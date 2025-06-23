/**
 * Simple HTTP Server using sockets in C.
 * 
 * Author: Ben  
 * Date: 2024-10  
 */

#include <stdio.h>	/* printf		*/
#include <errno.h>	/* perror		*/
#include <sys/socket.h>	/* socket bind 		*/
#include <string.h>	/* strtok strlen	*/
#include <netinet/in.h>	/* sockaddr_in		*/
#include <arpa/inet.h>	/* inet_pton		*/
#include <unistd.h>	/* close		*/
#include <sys/types.h>	/* sethostname		*/
#include <fcntl.h>	/* open read close	*/
#include <signal.h>	/* sigaction		*/


int 	fd;
int 	server_fd, client_fd;


void signal_handler(int sig)
{
        printf("\nShutting down the server...\n");

	if (sig == SIGINT)
	{
		if (fd)
		{
			close(fd);
		}
		
		if (client_fd)
		{
			close(client_fd);
		}
		
		if (server_fd)
		{
			shutdown(server_fd, SHUT_RDWR);
			close(server_fd);
		}
	}
}


int main()
{
	char *host_name = "FunDownload.kim";
	char 	*filename;
	char	file_content[10000];
	struct sockaddr_in server_addr, client_addr;
	struct linger linger_opt;
	socklen_t client_len = sizeof(client_addr);
	
	/*********************************************
	 * Handler variables
	 */
	char buffer[1024];
	int bytes_read = 0;
	char *request_line = NULL;
	char *method = NULL;
	char *url = NULL;
	char *http_version = NULL;
	char *response = NULL;
	
	signal(SIGINT, signal_handler);
	
	if (sethostname(host_name, strlen(host_name)) < 0)
	{
		perror("Assigning Hostname Failed!\n");
		return -1;
	}
	
	/*********************************************
	 * Create a Socket
	 */
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("Failed opening Socket\n");
		return -1;
	}
	
	linger_opt.l_linger = 0;
	setsockopt(server_fd, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000);
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
	
	/*********************************************
	 * Bind a Socket
	 */
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Bind Failed!\n");
		return -1;
	} 
	
	if (listen(server_fd, 3) < 0)
	{
		perror("Listen Failed!\n");
		return -1;
	}
	
	printf("HTTP server is listening on PORT 8000...\n");
	
	while (1)
	{
		/*********************************************
		 * Accept incoming connection
		 */	
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
		if (client_fd < 0)
		{
			perror("Accept Failed!\n");
			return -1;
		}
		
		/*********************************************
		 * Handle request
		 */
		bytes_read = recv(client_fd, buffer, 1024, 0);
		if (bytes_read <= 0)
		{
			close(client_fd);
			continue;
		}
		
		buffer[bytes_read] = '\0';
		request_line = strtok(buffer, "r\n");
		method = strtok(request_line, " ");
		url = strtok(NULL, " ");
		http_version = strtok(NULL, "r\n");
		
	        printf("Request: %s %s %s\n", method, url, http_version);

		/*********************************************
		 * Response
		 */
		response = "HTTP/1.1 200 OK\r\nContent-type: text/plain\r\n\r\nHello, World!";
		send(client_fd, response, strlen(response), 0);
		
		/*********************************************
		 * Recieve File Request for Download 
		 */
		
		/*
		memcpy(filename,  (char*)buffer + 1, 1023);
		
		fd = open(filename, O_RDONLY);
		read(fd, file_content, 10000);
		close(fd);
		send(client_fd, file_content, 10000, 0);*/
		
		/*********************************************
		 * Close Client Socket
		 */
		close(client_fd);
	}
	
	shutdown(server_fd, SHUT_RDWR);
	close(server_fd);
}
