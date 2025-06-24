# 
# Remote Syslog Forwarder (UDP) - Python Script
# ---------------------------------------------
# Author: Ben
# Date Reviewed: 08.10
#
# Description:
# ------------
# This script logs local system messages using the `syslog` module and forwards 
# messages with severity WARNING or higher to a remote syslog server over UDP.
#
# Functionality:
# --------------
# - `log_message(priority, message)`: Logs both locally (via syslog) and remotely.
# - `send_to_server(message, priority)`: Sends messages of priority >= WARNING to
#   a configured remote syslog server using the syslog format.
#
# Key Settings:
# -------------
# - `REMOTE_SERVER_IP`: IP address of the remote syslog receiver.
# - `REMOTE_SERVER_PORT`: UDP port for the remote syslog service (default: 514 or custom).
# - `syslog.openlog(...)`: Configures syslog to tag logs with "TestScript".
#
# Behavior:
# ---------
# - The script runs in an infinite loop.
# - Every 10 seconds, it sends 3 messages: INFO, WARNING, and ERROR.
# - Only WARNING and ERROR are forwarded to the remote server.
#
# Notes:
# ------
# - Ensure that the remote syslog server is listening on the correct port.
# - Make sure firewall rules allow outbound UDP packets to that port.
# - Local syslog daemon may need configuration to also display or store these logs.
#
# Example Output (Remote Server):
# <4>This is a warning message
# <3>This is an ERROR message
#


import syslog
import socket
import time

REMOTE_SERVER_IP = "192.168.1.100"
REMOTE_SERVER_PORT = 500

def send_to_server(message, priority):
    if priority >= syslog.LOG_WARNING:
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            syslog_message = f"<{priority}>{message}"
            sock.sendto(syslog_message.encode(), (REMOTE_SERVER_IP, REMOTE_SERVER_PORT))
            sock.close()
        except Exception as e:
            syslog.syslog(syslog.LOG_ERR, f"Failed to send remote syslog: {str(e)}")
            
syslog.openlog("TestScript", syslog.LOG_PID, syslog.LOG_USER)

def log_message(priority, message):
    syslog.syslog(priority, message)
    send_to_server(message, priority)

while True:
    log_message(syslog.LOG_INFO, "This is an info message")
    log_message(syslog.LOG_WARNING, "This is a warning message")
    log_message(syslog.LOG_ERR, "This is an ERROR message")

    time.sleep(10)
    
syslog.closelog()

