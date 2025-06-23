# Simple VPN Tunnel Project

This project implements a basic VPN tunnel using TUN/TAP interfaces in Linux. It creates a virtual network interface (`tun0`), sets up routing and NAT rules, and forwards encrypted UDP packets between the client and server.

---

## Features

- Create and configure TUN virtual network interface
- Setup IP routing and firewall (iptables) rules
- UDP socket communication for VPN tunnel packets
- Basic packet loop with placeholders for encryption/decryption
- Signal handling for graceful cleanup

---

## Requirements

- Linux system with `/dev/net/tun` device enabled
- Root privileges (for creating TUN devices and modifying network settings)
- GCC or compatible C compiler
- `iptables` and `ip` utilities available in PATH

---

## Files

- `vpn.h` — Shared header with declarations and macros
- `vpn_client.c` — Client implementation (use `AS_CLIENT` macro)
- `vpn_server.c` — Server implementation
- (Optional) `Encrypt()` and `Decrypt()` placeholders for packet encryption

---

