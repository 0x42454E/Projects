# UDP Broadcast Message Sender in C

This project demonstrates how to send **UDP broadcast messages** in C using a socket configured for broadcasting. It's useful for sending data to all hosts on a local subnet simultaneously.

---

## 📁 Project Structure

tcp_udp_ping_pong_exec_4_broadcast.c # Core logic to send UDP broadcasts
tcp_udp_ping_pong_exec_4.h # Header file with includes and guards




🧠 How It Works
The program creates a UDP socket.

Enables the SO_BROADCAST option.

Sets the target address to a broadcast address (10.10.3.255) and port (5000).

Continuously sends the message "bip" to all devices on the subnet every 5 seconds.




📌 Requirements
Linux system

GCC compiler

A configured broadcast interface matching the address 10.10.3.255