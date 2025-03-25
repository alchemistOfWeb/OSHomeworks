#include <iostream>
#include <sys/socket.h>


#define REQUEST "GET / HTTP/ 1.1\r\nHost: httpforever.com

// rpc - remote procedure call

void send_msessages(const char* msg, int size, int sender) {
    int sent = send();
    if (sent == -1) perror(errno);
}

int main() {
    struct sockaddr_in server_address;
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket creation error");
        exit(errno);
    }

    server_adderess.sin_addr.s_addr = inet_addr("...");
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);



    std::string msg = REQUEST;
    int sent = send(client_socket, msg.c_str(), msg.size(), 0);
    if (sent == -1) exit(errno);

    char buffer[3001];
    int rs = recv(client_socket, buffer, 3000, 0)
    if (rs) {
        
    }
...
    
    close(server_socket);
}
