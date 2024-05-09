// tcpc.c
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
/*
socket()
fill server fields
connect()
recv()
*/
void main() {
	struct sockaddr_in server;
	char buffer[100];
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 8080;
	connect(sockfd, (struct sockaddr*)&server, sizeof(server));
	recv(sockfd, buffer, 100, 0); // client receives the message
	printf("Message received is: %s", buffer);
	close(sockfd);
}