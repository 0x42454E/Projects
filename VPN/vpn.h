#ifndef __VPN_H__ 
#define __VPN_H__

#define _ISOC99_SOURCE
#include <linux/if.h> 			/* struct ifr and options	*/
#include <linux/if_tun.h>		/* set tun interface		*/
#include <sys/ioctl.h>			/* set tun interface		*/
#include <sys/socket.h>			/* sockets			*/
#include <sys/types.h>			/* file sys operations		*/
#include <sys/stat.h>			/* file sys operations		*/
#include <netdb.h>			/* netwroks addr manipulation	*/
#include <string.h>			/* strncpy			*/
#include <sys/select.h>			/* bzero			*/
#include <stdlib.h>			/* memset			*/
#include <stdio.h>			/* snprintf printf		*/
#include <signal.h>			/* sigaction			*/
#include <assert.h>			/* error messages		*/
#include <unistd.h>			/* open function		*/
#include <fcntl.h>			/* manipulate file descriptors	*/

#define AS_CLIENT YES 
#define SERVER_HOST "10.8.0.1" 


#define PORT 5001
#define MTU 1400
#define BIND_HOST "0.0.0.0"




int InitTun(void);
void run(char *cmd);
void IpConfig(void);
void SetupRouteTable(void);
void CleanupRouteTable(void);
int UdpBind(struct sockaddr *addr, socklen_t *addrlen);
void Cleanup(int signo);
void CleanupUponSigExit(void);
/*void Encrypt();
void Decrypt();*/





















#endif 				/*	__VPN_H__	*/
