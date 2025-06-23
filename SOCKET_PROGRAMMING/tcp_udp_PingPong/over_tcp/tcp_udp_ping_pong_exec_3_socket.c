#include <sys/types.h>
#include "tcp_udp_ping_pong_exec_3.h"

void RecieveMessage(struct sockaddr_in* cli_addr, socklen_t* cli_len, char* message, int message_length, int sockfd)
{
	char 	buffer[1024];
	int	client_sockfd = 0;

	/*********************************************
	 * Accepty incoming connection
	 */
		cli_addr->sin_addr.s_addr = inet_addr("10.10.2.60");
		
		client_sockfd = accept(sockfd, (struct sockaddr *)&cli_addr, cli_len);
		if (client_sockfd)
		{
			perror("Accepting...\n");
		}
	
			printf("%u Ip address:\n", cli_addr->sin_addr.s_addr);
	printf("Accepted connectio from client...\n");
	
	while (1)
	{
		/*********************************************
	 	* Recieve response
	 	*/
	 	recv(client_sockfd, buffer, 1024, 0);
	 	printf("Recieved\n");
	 	
		send(client_sockfd, message, message_length, 0);
		printf("Sent %s to server\n", message);	

	}
}

void SendMessage(char* message, int message_length, int sockfd)
{
	char 	buffer[1024];
	/*********************************************
	 * Send message
	 */
	while (1)
	{
		send(sockfd, message, message_length, 0);
		printf("Sent %s to server\n", message);
		
		/*********************************************
	 	* Recieve message response
	 	*/
	 	recv(sockfd, buffer, 1024, 0);
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
	inet_pton(AF_INET, "10.10.2.46", &serv_addr.sin_addr);
	
	/*********************************************
	* Bind address and port to socket
	*/
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Bind Failed!\n");
		return;
	}
	
	if (listen(sockfd, 5) < 0)
	{
		perror("Listening Failed!\n");
		return;
	}
	
	printf("%d Ping Pong session established\n", socket_type);
	printf("Server Listening on port %d...\n", port_num);
	
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
	inet_pton(AF_INET, "10.10.2.46", &serv_addr.sin_addr);
	
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Connect Failed\n");
		return;
	}
	
	printf("%d Ping Pong session established\n", socket_type);
	

	SendMessage(message, message_length, sockfd);
	

	close(sockfd);
}
