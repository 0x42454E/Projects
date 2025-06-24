***Penetration Testing Report
for Yolo CTF***

**Completion date**: 25.3.25

**Tester**: Ben Student

 **Client**:  www.yolo.co.il website
  
 **Confidentiality Notice**: 
 the report is confidential and should be handled securely.



***Summary***

**Scope**: 
External and internal networks
DMZ
active services and applications

**Objectives**:
Identify security weaknesses 
Locate flags

**High-Level Findings** & **Risk Rating**:
Exposure of private files and credentials - HIGH
Weak credentials policy enforced - HIGH
Credentials reuse - HIGH
Usage of insecure protocols - HIGH
Absence of access control - CRITICAL
Lack of security mechanisms - CRITICAL

**Overall Security Posture**:
Most common security measures exist

**Recommendations Summary**:
Reevaluate assets worth and adapt security accordingly 




***Methodology**:*

**Testing Approach**:
Black-box Testing
Manual and automated scanning

**Tools Used**: 
Nmap 
Nikto
Hydra 
John the ripper
gobuster
dirb
dsnenum
dig 
nslookup
ping
hping3
curl
netdiscover
wireshark
python - socket programming  
developers tools 
lighthouse
netcat
ProFTP
tcpdump
arpspoof
dnsspoof
ntpq
bash scripts



***Findings & Vulnerabilities**:*

**Exposure of private files and credentials**
severity: HIGH
Affected Systems: http://admin.yolo.co.il/backup/
Description: No access control and no permission required 
PoC: simple dnsenum on main domain exposes the admin subdomain
and dirb finds http://admin.yolo.co.il/backup/
Impact: Access to credentials and system-wide configuration file 
getting access to inside services through ssh protocol
Remediation steps: Delete from backup or enforce proper permissions 
References: OWASP 10 | CVSS | CIS Benchmarks


**Weak credentials policy enforced** 
severity: HIGH
Affected Systems: main domain and all subdomain and services
Description: Weal Credentials were found and brute force attempts easily cracked all present passwords
PoC: In backup directory shadow file was found with following hash -
dexter:$y$j9T$FVrhmaG8xav3NzNyqvkUN.$cKOnOMgGXDigPZRfgnGLP9egOrZgHmqVmPIOwXgB2zD:iloveyou1
Impact: all services and restrictions placed on the workspace of user dexter were easily accessed in the system  
Remediation steps: change passwords and use unique samples
Optionally, use unique nicknames as well
References: OWASP 10 | NIST | CIS | CVSS


**Credentials reuse** 
severity: HIGH
Affected Systems: main domain and all subdomain and services
Description: Credentials reuse were found and brute force attempts easily cracked all present passwords
PoC: In backup directory shadow file was found with following hash -
dexter:$y$j9T$FVrhmaG8xav3NzNyqvkUN.$cKOnOMgGXDigPZRfgnGLP9egOrZgHmqVmPIOwXgB2zD:iloveyou1
same one was found in the docker 192.168.3.1
impact: all services and restrictions placed on the workspace of user dexter were easily accessed in the system  
Remediation steps: change passwords and use unique samples
References: OWASP 10 | NIST | CIS | CVSS


**Usage of insecure protocols** 
severity: HIGH
Affected Systems: www.yolo.co.il and subdomains | ftp.yolo.co.il | dns.yolo.co.il
Description: No https for web access 
ftp service un-encrypted 
dns service un-encrypted 
PoC: all traffic seen through net sniffing tools
Impact: data ex filtration and credentials theft 
injection of altered content 
hijacking traffic to malicious services  
Remediation steps: use encrypted protocols
0References: OWASP 10 | NIST | CIS | CVSS


**Absence of access control** 
severity: CRITICAL
Affected Systems: All intranet
Description: inside the LAN no restrictions or anomaly detection were enforced which allowed for probing and spoofing of traffic for malicious purposes and actively seeking for weak spots 
PoC: No restriction were placed on all and any tools used through the testing
Impact: Location and testing of weak points were possible for unrestricted time frame
which brought to lateral movement and further privilege escalation  
Remediation steps: Enforcement of basic intranet security tools and monitoring can lower the threat level
References: OWASP 10 | NIST | CIS | CVSS


**Lack of security mechanisms**
severity: CRITICAL
Affected Systems: FTP | DNS | www.yolo.co.il | 
192.168.2.0/24 and 192.168.3.0/24 subnets and devices
Description: Only basic anti brute-force mechanisms were implemented
which exposed the system to probing for exploits attempts
Impact: FTP were accessed spoofed and manipulated 
DNS were spoofed and allowed lateral movement
main domain were exposed to active reconnaissance
Remediation steps: Implement security tools or policies
encrypted dns and ftp
proper sanitation of ftp-extracted content
ids/ips tools on endpoints or on network intersections
References: OWASP 10 | NIST | CIS | CVSS




***Risk Analysis & Remediation Plan***
The overall security was heavily compromised and could  bring severe consequences.
Implementing proper secure protocols and services can greatly elevate most of the weak points.
Usage of security tools for the different vulnerabilities and monitoring is heavily advised. 




***Conclusion & Next Steps***
Updating the protocols and services
Updating the security architecture 
Reeducate stuff and personal 
Update policies 
Implement POLP and Zero-Trust principles
Implement DLP 


***Appendices***
All tries and steps starting from the reconnaissance part present in the attached
file "reconnaissance"



