#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <pthread.h>
#include <netdb.h>
#include <fcntl.h>


#define HOST "httpforever.com"
#define PORT "80"
#define REQUEST "GET / HTTP/1.1\r\nHost: httpforever.com\r\nConnection: close\r\n\r\n"
#define BUFFER_SIZE 4096

int main(){

    //////////////////////

    struct addrinfo hints{}, *res;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(HOST, PORT, &hints, &res) != 0) {
        perror("getaddrinfo error: ");
        exit(errno);
    }

    int client_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    if (client_socket == -1) {
        perror("socket creation error");
        freeaddrinfo(res);
        exit(errno);
    }

    if (connect(client_socket, res->ai_addr, res->ai_addrlen) == -1) {
        perror("connection failed");
        close(client_socket);
        freeaddrinfo(res);
        exit(errno);
    }

    freeaddrinfo(res);

    if (send(client_socket, REQUEST, strlen(REQUEST), 0) == -1) {
        perror("Send failed");
        close(client_socket);
        exit(errno);
    }

    // std::ofstream outfile("httpforever.html", std::ios::binary);
    int output_fd = open("httpforever.html", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (output_fd == -1) {
        perror("file open failed");
        close(client_socket);
        exit(errno);
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        // outfile.write(buffer, bytes_received);
        if (write(output_fd, buffer, bytes_received) == -1) {
            perror("file write error");
            close(output_fd);
            close(client_socket);
            exit(errno);
        }
    }

    if (bytes_received == -1) {
        perror("Erorr during getting response");
    }

    close(output_fd);
    close(client_socket);
    std::cout << "response saved to httpforever.html" << std::endl;
    return 0;
}