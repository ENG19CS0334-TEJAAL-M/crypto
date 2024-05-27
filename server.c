#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        error("Error opening socket");
    }

    // Initialize server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket to the specified port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        error("Binding failed");
    }

    // Listen for incoming connections
    listen(server_socket, 5);
    printf("Server listening on port %d...\n", PORT);

    // Accept connection from client
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
    if (client_socket < 0) {
        error("Error accepting connection");
    }

    printf("Connection accepted from client\n");

    // Receive data from client
    int numbers[3];
    int bytes_received = recv(client_socket, numbers, sizeof(numbers), 0);
    if (bytes_received < 0) {
        error("Error receiving data from client");
    }

    // Calculate sum, difference, and product
    int sum = numbers[0] + numbers[1] + numbers[2];
    int difference = numbers[0] - numbers[1] - numbers[2];
    int product = numbers[0] * numbers[1] * numbers[2];

    // Send result back to client
    int results[3] = {sum, difference, product};
    int bytes_sent = send(client_socket, results, sizeof(results), 0);
    if (bytes_sent < 0) {
        error("Error sending data to client");
    }

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
