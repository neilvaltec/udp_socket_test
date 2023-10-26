#include <iostream>
#include <cstring>  // For std::memset

// Include headers for socket programming
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    const std::string UDP_IP = "127.0.0.1";
    const int UDP_PORT = 8080;

    // Create UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        std::cerr << "Error: Could not create socket." << std::endl;
        return 1;
    }

    // Bind to the local address
    struct sockaddr_in my_addr;
    std::memset(&my_addr, 0, sizeof(my_addr));  // Clear the struct
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(UDP_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1) {
        std::cerr << "Error: Could not bind to address." << std::endl;
        close(sock);
        return 1;
    }

    std::cout << "Listening on " << UDP_IP << ":" << UDP_PORT << std::endl;

    while (true) {
        char buffer[1024];
        struct sockaddr_in from_addr;
        socklen_t from_len = sizeof(from_addr);

        ssize_t bytes_received = recvfrom(sock, buffer, sizeof(buffer)-1, 0, (struct sockaddr*)&from_addr, &from_len);

        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';  // Null terminate the received data
            std::cout << "received message: " << buffer << " from " << inet_ntoa(from_addr.sin_addr) << ":" << ntohs(from_addr.sin_port) << std::endl;
        }
    }

    // Ideally, you'd want to close the socket when done, but in this endless loop you'll never reach this.
    // close(sock);

    return 0;
}
