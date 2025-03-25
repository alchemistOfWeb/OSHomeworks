#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <pthread.h>


void* receiveMessages(void* arg) {
    int client_socket = *(int*)arg;
    char buffer[1024];

    while (true) {
        ssize_t received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (received <= 0) break;

        if (received <= 0) {
            std::cout << "Server disconnected.\n";
            close(client_socket);
            exit(0);
        }
        buffer[received] = '\0';
        std::cout << buffer << "\n";
    }

    return nullptr;
}


int main(){

    // server address 
    struct sockaddr_in server_address;

    // create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
            perror("socket creation error");
            exit(errno);
    }

    // fill the server ip and port address 
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);

    // connect
    int connected = connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    if(connected == -1){
        perror("connection failed");
        exit(errno);
    }

    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);
    send(client_socket, username.c_str(), username.size(), 0);

    pthread_t receiver_thread;
    pthread_create(&receiver_thread, nullptr, receiveMessages, &client_socket);
    pthread_detach(receiver_thread);

    // send message to server
    std::string mess;
    std::cout << "\nConnected successfully with username " << username << "\nCommands:\n"
        << "\\exit - to exit program"
        << "\\list - list of users connected to server" << std::endl;


    while(true) {
        // std::cout << "Enter your message: ";
        std::getline(std::cin, mess);

        if (mess == "/exit") {
            close(client_socket);
            return 0;
        }

        // if (mess == "/list") {
        //     break;
        // }
        
        int sent = send(client_socket, mess.c_str(), mess.size(), 0);
        if(sent == -1){
            perror("sending failed");
            break;
        }
    }

    close(client_socket);
    return 0;
}