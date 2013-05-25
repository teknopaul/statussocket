#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 512
#define NPACK 10

void diep(char *s)
{
	perror(s);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in si_me;
	struct sockaddr_in si_other;
	int s, i, port;
	unsigned int slen = sizeof(si_other);
	char buf[BUFLEN];

	if ( (s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1 ) {
		diep("socket");
		return 1;
	}
	
	port = 9999;
	if (argc > 1) {
		port = atoi(argv[1]);
		if (port == 0) port = 9999;
	}
	
	memset((char *) &si_me, 0, sizeof(si_me));
	
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(port);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// cast to consst to avoid warnings
	const struct sockaddr * csi_me = (const struct sockaddr *)&si_me;
	
	if ( bind(s, csi_me, sizeof(si_me)) == -1 ) {
		diep("bind");
		return 1;
	}
	printf("Listening on %d\n", port);

	for ( i = 0 ; i < NPACK ; i++) {
		
		if ( recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_other, &slen) == -1 ) {
			diep("recvfrom()");
		}
		
		printf("Received packet from %s:%d\nData: %s\n\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
		
		FILE *cmd_file = fopen("/var/ops/command", "w+");
		if (cmd_file == NULL) {
			diep("Cant write to /var/ops/command");
			return 1;
		}
		fputs(buf, cmd_file);
		fclose(cmd_file);
	}

	close(s);
	return 0;
}
