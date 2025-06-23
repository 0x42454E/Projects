# Compiler and flags
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -Iinclude

# Source files and output directories
HEADERS = tcp_udp_ping_pong_exec_3.h
SERVER_SRC = tcp_udp_ping_pong_exec_3_server.c
CLIENT_SRC = tcp_udp_ping_pong_exec_3_client.c
SERVER_BIN = server
CLIENT_BIN = client

# Clean up build artifacts
clean:
	rm -f $(CLIENT_BIN)

# Build client
$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_SRC)

# Build server
$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_SRC)

