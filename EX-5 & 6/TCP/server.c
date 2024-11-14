#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>  // To use pow() for power calculation

void func(int confd) {
    int base, exponent, result;

    // Read base from the client
    read(confd, &base, sizeof(base));
    printf("\nThe base value is: %d", base);

    // Read exponent from the client
    read(confd, &exponent, sizeof(exponent));
    printf("\nThe exponent value is: %d", exponent);

    // Calculate base^exponent
    result = (int)pow(base, exponent);
    printf("\nThe result (base^exponent) is: %d\n", result);

    // Send the result back to the client
    write(confd, &result, sizeof(result));
}

int main() {
    int sockfd, confd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    // Socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed\n");
        return 1;
    } else {
        printf("Socket created successfully\n");

        // Assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(43451);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Binding socket
        if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
            printf("Bind failed\n");
            return 1;
        } else {
            printf("Bind successful\n");

            // Listen for client connections
            if (listen(sockfd, 5) == -1) {
                printf("Listen failed\n");
                return 1;
            } else {
                printf("Server listening\n");

                len = sizeof(cliaddr);
                confd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
                if (confd == -1) {
                    printf("Accept failed\n");
                    return 1;
                } else {
                    printf("Server accepted the client\n");
                    func(confd);  // Function to handle the client request
                }
            }
        }
    }

    // Close the sockets
    close(confd);
    close(sockfd);
    return 0;
}
