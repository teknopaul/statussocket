/*
 *
 * Name: sendudp
 * Version: 1.0
 * Owner: Ahmed Jolani
 * Email: ahmed.jolani@gmail.com
 * License: Commons Attribution 3.0 License (CC3)
 * Description: sendudp is a tool that allow you to test any UDP port, sendudp doesn't
 * guarantee the delivery of the sent packets, it only send the packets for you to test your
 * UDP application/software. Feel free to contribute to this tool and enhance it, please
 * email me with any contribution to keep me updated.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <getopt.h>

#define SIZE 1024
#define True 1
#define False 0

int index_of(char * string, char character) {
	int i = 0;
	while (string[i] != '\0') {
		if (string[i] == character) {
			return i;
		}
		i++;
	}
	return -1;
}

int main(int argc, char * argv[]) {
	
	if (argc < 5 ) {
		fprintf(stderr, "Usage %s -d host:port -m message\n", argv[0]);
		return 2;
	}
	
	int socket_fd, rv, pos;
	struct addrinfo hints, * res, * p;
	memset(&hints, 0, sizeof hints);
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_family = AF_UNSPEC;
	char *message;
	char ip[INET6_ADDRSTRLEN], port[8];
	
	memset((char *) ip, 0, INET6_ADDRSTRLEN);
	memset((char *) port, 0, 8);
	message = "ping";

	int ch;
		 
	opterr = 0;
		 
	while ((ch = getopt (argc, argv, "d:m:")) != -1) {
		switch (ch)
		{
			case 'd':
				pos = index_of(optarg, ':');
				if (pos > -1) {
					strncpy(ip, optarg, pos);
					strncpy(port, optarg + pos + 1, 8);
				}
				else {
					fprintf(stderr, "Specify host:port\n");
					return 2;
				}
				break;
			case 'm':
				message = optarg;
				break;
			case '?':
				if (optopt == 'd') {
					fprintf(stderr, "Specify host:port\n");
				}
				if (optopt == 'm') {
					fprintf(stderr, "Specify message to send\n");
				}
				else {
					fprintf(stderr, "Unknown option character `\\x%x'\n", optopt);				 
				}
				return 2;
			default:
				return 2;
		}
	}

	//fprintf(stdout, "host:port %s:%s\n", ip, port);
	rv = getaddrinfo(ip, port, &hints, &res);
	if (rv != 0) {
		fprintf(stderr, "Error [getaddrinfo]\n");
		return 2;
	}

	for (p = res; p != NULL; p = p->ai_next) {
		
		if ((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			fprintf(stderr, "Error [socket]\n");
			continue;
		}

		break;
	}

	freeaddrinfo(res);

	if (p == NULL) {
		fprintf(stderr, "Error [socket allocation]\n");
		return -2;
	}

	int len = strlen(message);
	
	int bytesSent = sendto(socket_fd, message, len > 1024 ? 1024 :  len, 0, p->ai_addr, p->ai_addrlen);
	if (bytesSent == -1) {
		fprintf(stderr, "Error [socket send]\n");
		return -2;
	}
	
	return 0;
	
}