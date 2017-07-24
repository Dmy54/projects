#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT "3333"
#define IPv4 "87.238.96.18"

int main(){

	char *buf[200];
	char *g = "ff";
	struct in_addr;
	struct sockaddr_in sa;
	int sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	sa.sin_family = AF_INET;
	sa.sin_port = PORT;
	sa.sin_addr.s_addr= IPv4;

	connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));

	recv(sockfd, buf, strlen(buf), 0);

	close(sockfd);

	return 0;
}