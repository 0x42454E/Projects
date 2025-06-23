#include "tcp_udp_ping_pong_exec_2.h"

void RecieveMessage(struct sockaddr_in *cli_addr, socklen_t* cli_len, char* message, int message_length, int sockfd)
{
	char 	buffer[1024];
	
	while (1)
	{
		/*********************************************
	 	* Recieve response
	 	*/
	 	recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)cli_addr, cli_len);
	 	printf("Recieved %s response from server: %s\n", message, buffer);
	 	
		sendto(sockfd, message, message_length, 0, (struct sockaddr *)cli_addr, *cli_len);
		printf("Sent %s to server\n", message);	
	}
}

void SendMessage(struct sockaddr_in *serv_addr, socklen_t serv_addr_len, char* message, int message_length, int sockfd)
{
	char 	buffer[1024];
	/*********************************************
	 * Send message
	 */
	while (1)
	{
		sendto(sockfd, message, message_length, 0, (struct sockaddr *)serv_addr, serv_addr_len);
		printf("Sent %s to server\n", message);
		
		/*********************************************
	 	* Recieve message response
	 	*/
	 	recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)serv_addr, &serv_addr_len);
	 	printf("Recieved %s response from server.\n", buffer);
	}
}

void CreateServerSocket(int port_num, int socket_type, char* message, int message_length)
{
	struct 	sockaddr_in serv_addr, cli_addr;
	socklen_t cli_len = sizeof(cli_addr);
	int 	sockfd = socket(AF_INET, socket_type, 0);
	/*********************************************
	 * create a socket_type socket
	 */
	if (sockfd < 0)
	{
		perror("Socket Creation Failed\n");
		return;
	}
	/*********************************************
	* Set address and port
	*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_num);
	inet_pton(AF_INET, "127.0.0.2", &serv_addr.sin_addr);
	
	/*********************************************
	* Bind address and port to socket
	*/
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Bind Failed!\n");
		return;
	}
	
	printf("%d Ping Pong session established\n", socket_type);
	
	RecieveMessage(&cli_addr, &cli_len, message, message_length, sockfd);

	close(sockfd);
}

void CreateClientSocket(int port_num, int socket_type, char* message, int message_length)
{
	struct 	sockaddr_in serv_addr;
	int 	sockfd = socket(AF_INET, socket_type, 0);
	/*********************************************
	 * create a socket_type socket
	 */
	if (sockfd < 0)
	{
		perror("Socket Creation Failed\n");
		return;
	}
	
	/*********************************************
	* Set address and port
	*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_num);
	inet_pton(AF_INET, "127.0.0.2", &serv_addr.sin_addr);
	
	printf("%d Ping Pong session established\n", socket_type);
	

	SendMessage(&serv_addr, sizeof(serv_addr), message, message_length, sockfd);
	

	close(sockfd);
}
