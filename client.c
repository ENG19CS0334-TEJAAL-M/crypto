#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        error("Error opening socket");
    }

    // Initialize server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        error("Invalid address/ Address not supported");
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        error("Connection failed");
    }

    printf("Connected to server\n");

    // Send three numbers to server
    int numbers[3] = {10, 5, 3};
    int bytes_sent = send(client_socket, numbers, sizeof(numbers), 0);
    if (bytes_sent < 0) {
        error("Error sending data to server");
    }

    printf("Sent numbers to server\n");

    // Receive result from server
    int results[3];
    int bytes_received = recv(client_socket, results, sizeof(results), 0);
    if (bytes_received < 0) {
        error("Error receiving data from server");
    }

    printf("Received results from server:\n");
    printf("Sum: %d\n", results[0]);
    printf("Difference: %d\n", results[1]);
    printf("Product: %d\n", results[2]);

    // Close socket
    close(client_socket);

    return 0;
}
