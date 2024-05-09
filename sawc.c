include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);// Creating socket file descriptor
    char buffer[100];
    struct sockaddr_in servaddr;

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = 8080;
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    while (1) {
        printf("Enter message: ");
        fgets(buffer, 100, stdin);
        
        sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        
        n = recvfrom(sockfd, (char *)buffer, 100, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
