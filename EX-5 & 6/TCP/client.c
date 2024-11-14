#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void func(int sockfd) {
    int base, exponent, result;
    
    // Input for base
    printf("\nEnter the base value: ");
    scanf("%d", &base);
    write(sockfd, &base, sizeof(base));
    
    // Input for exponent
    printf("\nEnter the exponent value: ");
    scanf("%d", &exponent);
    write(sockfd, &exponent, sizeof(exponent));
    
    // Read the result from the server
    read(sockfd, &result, sizeof(result));
    printf("\nThe result (base^exponent) is: %d\n", result);
}

void main() {
    int sockfd;
    struct sockaddr_in servaddr;

    // Socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("\nSocket creation failed\n");
    } else {
        printf("\nSocket created successfully\n");

        // Assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(43451);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Connect to the server
        if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
            printf("\nConnection failed\n");
        } else {
            printf("\nServer connected successfully\n");
            func(sockfd);  // Function to perform the task
        }
    }
    
    // Close the socket
    close(sockfd);
}
