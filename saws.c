//sawserver.c
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>


int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Creating socket file descriptor
    char buffer[100];
    struct sockaddr_in servaddr, cliaddr;

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = 8080;

    // Binding socket with server address
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    int n;
    socklen_t len;

    while (1) {
        len = sizeof(cliaddr);

        n = recvfrom(sockfd, (char *)buffer, 100, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        
        // Simulate corruption by adding a condition
        if (rand() % 2 == 0) {
            printf("Received corrupted message. Sending NAK.\n");
            sendto(sockfd, (const char *)"NAK", strlen("NAK"), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        } else {
            printf("Client : %s\n", buffer);
            sendto(sockfd, (const char *)"ACK", strlen("ACK"), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        }
    }

    close(sockfd);
    return 0;
}
