# UDP Ping-Pong Communication in C

This project demonstrates a **simple UDP-based Ping-Pong messaging system** in C between a client and a server running on the same machine via the loopback interface.

---

## 📁 Project Structure

tcp_udp_ping_pong_exec_2.h # Header file
tcp_udp_ping_pong_exec_2_socket.c # Core socket logic (send/receive + setup)
udp_server.c # Contains CreateServerSocket() usage
udp_client.c # Contains CreateClientSocket() usage


---

## 🧠 How It Works

- **Server** listens on `127.0.0.2:1234` and echoes back received messages.
- **Client** sends messages to the server and displays responses.
- Both client and server run in infinite loops, creating a continuous ping-pong exchange.

> Communication is done over **UDP**, and the socket type is passed as `SOCK_DGRAM`.

---

