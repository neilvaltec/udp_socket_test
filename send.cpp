#include <iostream>
#include <string>
#include <thread>
#include <chrono>
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
    const std::string MESSAGE = "Hello, World!";

    std::cout << "UDP target IP: " << UDP_IP << std::endl;
    std::cout << "UDP target port: " << UDP_PORT << std::endl;
    std::cout << "message: " << MESSAGE << std::endl;

    // Create UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        std::cerr << "Error: Could not create socket." << std::endl;
        return 1;
    }

    // Configure target address
    struct sockaddr_in target_addr;
    std::memset(&target_addr, 0, sizeof(target_addr));  // Clear the struct
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(UDP_PORT);
    inet_pton(AF_INET, UDP_IP.c_str(), &target_addr.sin_addr);

    while (true) {
        sendto(sock, MESSAGE.c_str(), MESSAGE.length(), 0, (struct sockaddr *)&target_addr, sizeof(target_addr));
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "message: " << MESSAGE << std::endl;
    }

    // Ideally, you'd want to close the socket when done, but in this endless loop you'll never reach this.
    // close(sock);

    return 0;
}
