#include "vpn.h"


int InitTun(void)
{	
	/****************************************
	 * Create a tunnel and return fd.
	 */
	 
	struct ifreq ifr;
	int 	fd, e;
	
	if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
	{
		perror("Cannot Create Tunnel\n");
		return fd;
	}
	
	memset(&ifr, 0, sizeof(ifr));
	
	/**********************************************
	 * set flags to specify tun device,
	 * and disable kernel's default header allocation.
	 * set struct name.
	 */
	 
	ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
	/*ifr.ifr_flags = IFF_TUN | IFF_MULTI_QUEUE;*/
	strncpy(ifr.ifr_name, "tun0", IFNAMSIZ);
	
	/**********************************************
	 * Configure tun interface,
	 * using the ioctl lib.
	 */
	 
	if ((e = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0)
	{
		perror("ioctl[TUNSETIFF]\n");
		close(fd);
		return e;
	}
	
	return fd;
}

void run(char *cmd)
{
	/**********************************************
	 * Execute CMD's.
	 */
	 
	 if (system(cmd))
	 {
	 	perror(cmd);
	 	exit(1);
	 }
}

void IpConfig(void)
{
	/***********************************************
	 * Configure IP address and MTU of VPN interface
	 */
	 
	 char cmd[1024];
	 char cmd2[1024];
	 
	 #ifdef AS_CLIENT
	 	snprintf(cmd2, sizeof(cmd2), "ifconfig tun0 10.8.0.2/16 mtu %d up", MTU);
	 #else 
	 	snprintf(cmd2, sizeof(cmd2), "ifconfig tun0 10.8.0.1/16 mtu %d up", MTU);
	 #endif
	 	run(cmd2);
}

void SetupRouteTable(void)
{
	/**********************************************
	 * Setup route table
	 */
	 
	char cmd[1024];
	run("sysctl -w net.ipv4.ip_forward=1");
	
	#ifdef AS_CLIENT
		run("iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE");
		run("iptables -I FORWARD 1 -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
		run("iptables -I FORWARD 1 -o tun0 -j ACCEPT");
		
		snprintf(cmd, sizeof(cmd), "ip route add %s via $(ip route show 0/0 | sed -e 's/.* via \\([^ ]*\\).*/\\1/')", SERVER_HOST);

		run(cmd);
		run("ip route add 0/1 dev tun0");
		run("ip route add 128/1 dev tun0");
	#else
		run("iptables -t nat -A POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -m comment --comment 'vpndemo' -j MASQUERADE");
		run("iptables -A FORWARD -s 10.8.0.0/16 -m state --state RELATED,ESTABLISHED -j ACCEPT");
		run("iptables -A FORWARD -d 10.8.0.0/16 -j ACCEPT");
	#endif
}

void CleanupRouteTable(void)
{
	/**********************************************
	 * Cleanup route table
	 */

	#ifdef AS_CLIENT
		char cmd[1024];
		run("iptables -t nat -D POSTROUTING -o tun0 -j MASQUERADE");
		run("iptables -D FORWARD -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
		run("iptables -D FORWARD -o tun0 -j ACCEPT");
		snprintf(cmd, sizeof(cmd), "ip route del %s", SERVER_HOST);
		run(cmd);
		run("ip route del 0/1");
		run("ip route del 128/1");
	#else 
		run("iptables -t nat -D POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -m comment --comment 'vpndemo' -j MASQUERADE");
		run("iptables -D FORWARD -s 10.8.0.0/16 -m state --state RELATED,ESTABLISHED -j ACCEPT");
		run("iptables -D FORWARD -d 10.8.0.0/16 -j ACCEPT");
	#endif 
}

int UdpBind(struct sockaddr *addr, socklen_t *addrlen)
{
	/**********************************************
	 * Bind UDP port
	 */
	
	struct addrinfo hints;
	struct addrinfo *result;
	const char *host;
	int sock, flags;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	
	#ifdef AS_CLIENT
		host = SERVER_HOST;
	#else 
		host = BIND_HOST;
	#endif 
		if (0 != getaddrinfo(host, NULL, &hints, &result))
		{
			perror("getaddrinfo error\n");
			return -1;
		}
	
	if (result->ai_family == AF_INET)
	{
		((struct sockaddr_in *)result->ai_addr)->sin_port = htons(PORT);
	}		
	
	else if (result->ai_family == AF_INET6)
	{
		((struct sockaddr_in6 *)result->ai_addr)->sin6_port = htons(PORT);
	}
	
	else
	{
		fprintf(stderr, "unknown ai_family %d\n", result->ai_family);
		freeaddrinfo(result);
		return -1;
	}
	
	memcpy(addr, result->ai_addr, result->ai_addrlen);
	*addrlen = result->ai_addrlen;
	
	if (-1 == (sock = socket(result->ai_family, SOCK_DGRAM, IPPROTO_UDP)))
	{
		perror("Cannot create socket\n");
		freeaddrinfo(result);
		return -1;
	}
	
	#ifndef AS_CLIENT
		if (0 != bind(sock, result->ai_addr, result->ai_addrlen))
		{
			perror("Cannot bind\n");
			close(sock);
			freeaddrinfo(result);
			return -1;
		}
	#endif 
	
		freeaddrinfo(result);
		
		flags = fcntl(sock, F_GETFL, 0);
		if (flags != -1)
		{
			if (-1 != fcntl(sock, F_SETFL, flags | O_NONBLOCK))
			{
				return sock;
			}
		}
		
		perror("fcntl error\n");
		
		close(sock);
		return -1;
}	

void Cleanup(int signo)
{
	/**********************************************
	 * Signal handler
	 */

	if (signo == SIGHUP || signo == SIGINT || signo == SIGTERM)
	{
		CleanupRouteTable();
		exit(0);
	}
}

void CleanupUponSigExit(void)
{
	/**********************************************
	 * Sigaction and handler assignment
	 */

	struct sigaction sa;
	sa.sa_handler = &Cleanup;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	
	if (sigaction(SIGHUP, &sa, NULL) < 0)
	{
		perror("Cannot handle SIGHUP\n");
	}
	
	if (sigaction(SIGINT, &sa, NULL) < 0)
	{
		perror("Cannot handle SIGINT\n");
	}
	
	if (sigaction(SIGTERM, &sa, NULL) < 0)
	{
		perror("Cannot handle SIGTERM\n");
	}
}

/*void Encrypt()
{

}

void Decrypt()
{
	
}*/
