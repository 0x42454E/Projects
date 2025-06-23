#include "tcp_udp_ping_pong_exec_4.h"

void SendMessage(struct sockaddr_in* broad_addr, socklen_t broad_len, char* message, int message_length, int sockfd)
{
	/*********************************************
	 * Send message
	 */
	sendto(sockfd, message, message_length, 0, (struct sockaddr *)broad_addr, broad_len);
	printf("Sent %s to EveryOne\n", message);
		
}

void CreateBroadcastSocket(int port_num, char* message, int message_length)
{
	struct 	sockaddr_in s;
	socklen_t s_len = sizeof(s);
	int 	broadcast_enable = 1;
	int 	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	/*********************************************
	 * create a socket_type socket
	 */
	if (sockfd < 0)
	{
		perror("Socket Creation Failed\n");
		return;
	}
	
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable));
	
	/*********************************************
	* Set address and port -- must be different for broadcast
	*/
	s.sin_family = AF_INET;
	s.sin_port = htons(port_num);
	inet_pton(AF_INET, "10.10.3.255", &s.sin_addr);

	printf("Sending Broadcast...\n");
	
	while (1)
	{
		SendMessage(&s, s_len, message, message_length, sockfd);
		sleep(5);
	}

	close(sockfd);
}
