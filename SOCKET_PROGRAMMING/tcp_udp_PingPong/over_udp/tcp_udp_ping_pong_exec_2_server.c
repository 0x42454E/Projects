/*********************************************
 * Server Source Code UDP
 */
#include <sys/socket.h>		/* for sending socket type	*/
#include <string.h>		/* strlen			*/
#include "tcp_udp_ping_pong_exec_2_socket.c"


int main()
{
	char* message = "ping";
	
	CreateServerSocket(1234, SOCK_DGRAM, message, strlen(message));
	
	return 0;
}
