#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <vector>
#include <map>

#define BUFFER_SIZE 1001


pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;
std::map<int, std::string> clients;

void broadcastMessage(const std::string& message, int sender) {
    pthread_mutex_lock(&output_mutex);
    for (const auto& [sock, name] : clients) {
        if (sock != sender) {
            if (send(sock, message.c_str(), message.size(), 0) == -1) {
                perror("Send failed");
            }
        }
    }
    pthread_mutex_unlock(&output_mutex);
}

void* handle_client(void* arg) {
    int client_socket = reinterpret_cast<intptr_t>(arg);

    char buffer[BUFFER_SIZE];
    int rs = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (rs <= 0) {
        close(client_socket);
        return nullptr;
    }
    buffer[rs] = '\0';

    pthread_mutex_lock(&output_mutex);
    clients[client_socket] = buffer;
    pthread_mutex_unlock(&output_mutex);

    broadcastMessage(std::string(buffer) + " joined the chat!", client_socket);

    while (true) {
        // Receive message from client
        rs = recv(client_socket, buffer, BUFFER_SIZE-1, 0);
        
        if (rs == -1) {
            perror("client socket connection error");
            break; 
        }

        if (rs == 0) {
            break; 
        }

        buffer[rs] = '\0';
        std::string message(buffer);
        if (message == "\\list") {
            pthread_mutex_lock(&output_mutex);
            std::string userList = "Connected users: ";
            for (const auto& [sock, name] : clients) {
                userList += name + " ";
            }
            std::cout << "requested list of users" << std::endl;
            pthread_mutex_unlock(&output_mutex);

            send(client_socket, userList.c_str(), userList.size(), 0);
            continue;
        }

        std::string fullMessage = clients[client_socket] + ": " + message;
        broadcastMessage(fullMessage, client_socket);
    }

    pthread_mutex_lock(&output_mutex);
    std::string leaveMsg = clients[client_socket] + " left the chat.";
    clients.erase(client_socket);
    pthread_mutex_unlock(&output_mutex);

    broadcastMessage(leaveMsg, client_socket);

    close(client_socket);
    return nullptr;
}


int main() {
    // create a socket  
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket creation error");
        exit(errno);
    }

    // create an endpoint
    
    // socket address
    struct sockaddr_in server_address;
    // internet protocol = AF_INET
    server_address.sin_family = AF_INET;
    // accept or any address (bind the socket to all available interfaces)
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    // port
    server_address.sin_port = htons(8888);

    // Bind server_socket to server_address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(errno);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) < 0) {
        perror("listen failed");
        exit(errno);
    }
    std::cout << "Waiting for connection\n";



    while(true) {
        int client_socket;
        struct sockaddr_in client_address;
        unsigned int client_addr_len = sizeof(client_address);

        // Accept incoming connection
        client_socket = accept(
            server_socket, 
            (struct sockaddr*) &client_address, 
            &client_addr_len);

        if (client_socket < 0) {
            perror("accept failed");
            // exit(errno);
            continue;
        }

        pthread_mutex_lock(&output_mutex);
        std::cout << "Connected client with address: " 
            << inet_ntoa(client_address.sin_addr) << "\n";
            
        pthread_mutex_unlock(&output_mutex);


        pthread_t thread_id;
        if (pthread_create(
                &thread_id, 
                nullptr, 
                handle_client, 
                reinterpret_cast<void*>(client_socket)
            ) != 0) {

            perror("pthread_create failed");
            close(client_socket);
        } else {
            pthread_detach(thread_id);
        }
    }
  
    // close
    close(server_socket);
    pthread_mutex_destroy(&output_mutex);
    return 0;
}
