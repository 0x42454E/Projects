/*********************************************
 * Server Source Code UDP
 */
#include <string.h>		/* strlen			*/
#include "tcp_udp_ping_pong_exec_4_broadcast.c"


int main()
{
	char* message = "bip";
	
	CreateBroadcastSocket(5000, message, strlen(message));
	
	return 0;
}
