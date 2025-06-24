[Suricata](https://suricata.io/) is a Network Security Monitoring (NSM) tool that uses sets of community created and user defined signatures (also referred to as rules) to examine and process network traffic. Suricata can generate log events, trigger alerts, and drop traffic when it detects suspicious packets or requests to any number of different services running on a server.

By default Suricata works as a passive Intrusion Detection System (IDS) to scan for suspicious traffic on a server or network. It will generate and log alerts for further investigation. It can also be configured as an active Intrusion Prevention System (IPS) to log, alert, and completely block network traffic that matches specific rules.

install:
```
sudo add-apt-repository ppa:oisf/suricata-stable
```

```
sudo apt install suricata
```
```
sudo systemctl enable suricata.service
```

configure:
```
sudo nano /etc/suricata/suricata.yaml
```

You may need to override the default network interface or interfaces that you would like Suricata to inspect traffic on.```
# Linux high speed capture support
af-packet:
  - interface: eth0
```

sudo suricata-update
```
sudo suricata-update list-sources

sudo suricata-update enable-source tgreen/hunting

Suricata has a built-in test mode that will check the configuration file and any included rules for validity:

sudo suricata -T -c /etc/suricata/suricata.yaml -v

running:
```
sudo systemctl start suricata.service
```

sudo tail -f /var/log/suricata/suricata.log

test:
```
curl http://testmynids.org/uid/index.html
```

The Suricata documentation recommends using the `jq` utility to read and filter the entries in this file:

  
sudo apt install jq

jq 'select(.alert .signature_id==2100498)' /var/log/suricata/eve.json


Overview:
Suricata is multi-threaded, which means that it can use multiple cores at once. Engaging multiple CPUs allows Suricata to process multiple events at the same time without having to interrupt other requests. Multi-threading also enables Suricata to load balance across the CPUs, as well as improve overall performance in network traffic analysis. This is advantageous because it means that Suricata can process large quantities of traffic without needing to cut back on rules.

**Flaws:**
1) cannot catch threats in packets of a encrypted/secured transmitted traffic in the network

The solution is to be more focused where you have visibility, which is at the endpoint.

use workstation endpoint protection.

2) A large input buffer to one of the following transforms can lead to a stack overflow causing Suricata to crash in the following transforms:

- to_lowercase
- to_uppercase
- strip_whitespace
- compress_whitespace
- dotprefix
- header_lowercase
- strip_pseudo_headers
- url_decode
- xor

3) A large BPF filter file provided to Suricata at startup can lead to a buffer overflow at Suricata startup.

Do not use untrusted files as an input to `suricata -F` command line option.

4)A specially crafted TCP stream can lead to a very large buffer overflow while being zero-filled during initialization with memset due to an unsigned integer underflow.

5)DNS resource name compression can lead to small DNS messages containing very large hostnames which can be costly to decode, and lead to very large DNS log records. While there are limits in place, they were too generous.

6) TCP streams with TCP urgent data (out of band data) can lead to Suricata analyzing data differently than the applications at the TCP endpoints, leading to possible evasions.

In IPS mode, you can use a rule such as `drop tcp any any -> any any (sid:1; tcp.flags:U*;)` to drop all the packets with urgent flag set.

7)Missing initialization of the random seed for "thash" leads to byte-range tracking having predictable hash table behavior. This can lead to an attacker forcing lots of data into a single hash bucket, leading to severe performance degradation.

8)
Invalid ALPN in TLS/QUIC traffic when JA4 matching/logging is enabled can lead to Suricata aborting with a panic.

JA4 is used in TLS and QUIC, and each is handled separately.

#### TLS

JA4 for TLS can be disabled in the `tls` section of the `app-layer` configuration by setting `ja4-fingerprints` to `false` (default: `auto`). For example:

```yaml
app-layer:
  tls:
    ja4-fingerprints: false
```

#### Quic

Quic does not have a JA4 feature flag and it is always enabled, so the recommendation is to disable Quic until Suricata can be updated, for example:

```yaml
app-layer:
  quic:
    enabled: false
```

9)A logic error during fragment reassembly can lead to failed reassembly for valid traffic. An attacker could craft packets to trigger this behavior.

10) Rules using datasets with the non-functional / unimplemented "unset" option can trigger an assertion during traffic parsing, leading to denial of service.
Use only trusted and well tested rulesets.

11) A memory allocation failure due to `http.memcap` being reached leads to a NULL-ptr reference leading to a crash.
Disable the `http.memcap` or set to a very large value.

12)  Crafted modbus traffic can lead to unlimited resource accumulation within a flow.
Disable the modbus parser if it is enabled. It is disabled by default.  
Set a limited stream.reassembly.depth to reduce the issue.

13) Suricata can run out of memory when parsing crafted HTTP/2 traffic.
Disable the HTTP/2 parser.

14) Mishandling of multiple fragmented packets using the same IP ID value can lead to packet reassembly failure, which can lead to policy bypass.
When using af-packet, enable `defrag` to reduce the scope of the problem.

15) Fragmentation anomalies may be reassembled incorrectly leading to mis-detection of rules.

16) Specially crafted traffic can cause a limited buffer overflow.

	Specially crafted datasets can cause a limited buffer overflow.

- Do not load untrusted datasets
- Do not use rules with `base64_decode` keyword with `bytes` option with value 1, 2 or 5

17) Small amount of HTTP/2 traffic can lead to Suricata using a large amount of memory.

Disable the HTTP/2 parser.

Reduce `app-layer.protocols.http2.max-table-size` value (default is 65536)

18) When parsing an overly long SSH banner, Suricata can use excessive CPU resources, as well as cause excessive logging volume in alert records.

19) Excessive memory use during pgsql parsing could lead to OOM-related crashes.

Disable pgsql app layer parser.

20) Specially crafted traffic can cause a heap use after free if the ruleset uses the http.request_header or http.response_header keyword.
Avoid the http.request_header and http.response_header keywords.

21) Rules inspecting HTTP2 headers can get bypassed by crafted traffic.

23) An attacker can craft traffic to cause Suricata to use far more CPU and memory for processing the traffic than needed, which can lead to extreme slow downs and denial of service.
Disable affected protocol app-layer parser in the yaml.  
A reduced `stream.reassembly.depth` value helps reduce the severity of the issue.