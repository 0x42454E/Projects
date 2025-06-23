# TCP Ping-Pong Communication in C

This project implements a simple **Ping-Pong messaging system over TCP** using C sockets. It includes both client and server programs that send and receive messages in a loop, simulating a real-time exchange between two systems.

---

## 📁 Project Structure

tcp_udp_ping_pong_exec_3.h # Header file
tcp_udp_ping_pong_exec_3_socket.c # Core socket logic (send/receive + setup)
tcp_udp_ping_pong_exec_3_client.c # Client logic
tcp_udp_ping_pong_exec_3_server.c # Server logic





🧠 How It Works

🔸 Server
Binds to 10.10.2.46:1234

Waits for incoming connections using listen()

Accepts connections with accept()

Receives data from the client and replies with the same message (ping-pong loop)

🔹 Client
Connects to the server at 10.10.2.46:1234

Sends a message (pong) and receives a response in a loop

Both sides use SOCK_STREAM (TCP)

📌 Important Notes
IP addresses are hardcoded as:

Server: 10.10.2.46

Client: connects to 10.10.2.46

Accepted client IP: simulated as 10.10.2.60

Ensure both addresses are reachable and assigned on your local network or interfaces.

Modify IPs if testing locally (e.g., use 127.0.0.1 for loopback).