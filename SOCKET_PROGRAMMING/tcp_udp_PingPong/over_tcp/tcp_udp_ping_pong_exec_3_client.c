/*********************************************
 * Client Source Code UDP
 */
#include <sys/socket.h>		/* for sending socket type	*/
#include <string.h>		/* strlen			*/
#include "tcp_udp_ping_pong_exec_3_socket.c"


int main()
{
	char* message = "pong";
	
	CreateClientSocket(1234, SOCK_STREAM, message, strlen(message));
	
	return 0;
}
