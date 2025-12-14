#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <netinet/tcp.h>
#include <source_location>
#include <string_view>
#include "log.h"



bool keep_running = true;

void signal_handler(int signum) {
    keep_running = false;
}

int main() {
    // Signal handler for clean exit on Ctrl+C (SIGINT)
    signal(SIGINT, signal_handler);

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int counter = 1;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        log_message("Socket failed");
        return -1;
    }
    


    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        log_message("Setsockopt failed");
        return -1;
    }

    int state = 1;
    if(setsockopt(server_fd, IPPROTO_TCP, TCP_CORK, &state, sizeof(state)) < 0) {
       log_message("TCP CORK FAILED");
       return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP
    address.sin_port = htons(12345);       // Use port 12345

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        log_message("Bind failed");
        return -1;
    }

    // Listen for incoming connections (1 client)
    if (listen(server_fd, 1) < 0) {
        log_message("Listen failed");
        return -1;
    }

    std::cout << "Server is broadcasting on 0.0.0.0:12345..." << std::endl;

    // Accept the incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        log_message("Accept failed");
        return -1;
    }

    std::cout << "Connection established with client." << std::endl;

    // Start broadcasting numbers
    while (keep_running) {
        std::string message = std::to_string(counter) + "\n";
        send(new_socket, message.c_str(), message.length(), 0);
        std::cout << "Sent: " << counter << std::endl;
        counter++;
    }

    std::cout << "\nBroadcasting stopped." << std::endl;



    state = 0;
    if(setsockopt(server_fd, IPPROTO_TCP, TCP_CORK, &state, sizeof(state) < 0)) {
       log_message("CORK DISABLED FAILED");
    }




    // Clean up: Close the socket
    close(new_socket);
    close(server_fd);

    return 0;
}

