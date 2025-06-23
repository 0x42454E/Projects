#include "vpn.h"

int main()
{
	struct sockaddr_storage client_addr;		/* client socket,  		*/
	socklen_t client_addrlen = sizeof(client_addr);	/* and length			*/
	char tun_buf[MTU], udp_buf[MTU];		/* tun device and udp buffers	*/
	fd_set readset;					/* reading input to buffers	*/
	int max_fd;					/* maximum value for select()	*/
	int udp_fd;					/* udp file descriptor		*/
	int r;						/* file descriptor read var 	*/
	
	/************************************************
	 * Initiating tun interace and returning tun's fd
	 */
	 
	int tun_fd;					
	if ((tun_fd = InitTun()) < 0)
	{
		return 1;
	}
	
	
	/**********************************************
	 * Initiating VPN routing and sig handlers
	 */
	 
	IpConfig();
	SetupRouteTable();
	CleanupUponSigExit();
	
	
	/**********************************************
	 * Bind udp's socket and return fd
	 * Initiating all buffers to zero on binary lvl
	 */
	 
	if ((udp_fd  = UdpBind((struct sockaddr *)&client_addr, &client_addrlen)) < 0)
	{
		return 1;
	}
	 
	memset(tun_buf, 0, MTU);
	memset(udp_buf, 0, MTU);
	
	/**********************************************
	 * Waiting for Packets 
	 */
	 
	while(1)
	{
		/**********************************************
	 	* Initiating POSIX select function
	 	* Empty the set of file descriptors 
	 	* Adding tun and udp file descriptors
	 	*/
	 	
		FD_ZERO(&readset);
		FD_SET(tun_fd, &readset);
		FD_SET(udp_fd, &readset);
		max_fd = (tun_fd > udp_fd ? tun_fd : udp_fd) + 1;

		
		if (-1 == select(max_fd, &readset, NULL, NULL, NULL))
		{
			perror("select error\n");
			break;
		}
		
		/**********************************************
	 	* Ensure tun/udp status is ready for reading
	 	* Read/writ from/to file descriptor to buffer
	 	* Send or recieve packets 
	 	* Encrypt and Decrypt 
	 	*/
	 
		if (FD_ISSET(tun_fd, &readset))
		{
			r = read(tun_fd, tun_buf, MTU);
			if (r < 0)
			{
				perror("read from tun_fd error\n");
				break;
			}
		
		
			/*Encrypt(tun_buf, udp_buf, r);*/
			
			r = sendto(udp_fd, udp_buf, r, 0, (const struct sockaddr *)&client_addr, client_addrlen);
			if (r < 0)
			{
				perror("sendto udp_fd error\n");
				break;
			}
		}
	
		if (FD_ISSET(udp_fd, &readset))
		{
			r = recvfrom(udp_fd, udp_buf, MTU, 0, (struct sockaddr *)&client_addr, &client_addrlen);
			if (r < 0)
			{
				perror("recvfrom udp_fd error\n");
				break;
			}
		
		
			/*Decrypt(udp_buf, tun_buf, r);*/
			
			r = write(tun_fd, tun_buf, r);
			if (r < 0)
			{
				perror("write tun_fd error\n");
				break;
			}
		}
	}
	
	close(tun_fd);
	close(udp_fd);
	
	CleanupRouteTable();
	
	return 0;
}	
