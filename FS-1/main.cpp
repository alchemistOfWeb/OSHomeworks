#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024


void readFile(char* filePath) {
    // do smth...
    int fd = open(filePath, O_RDONLY);
    if (fd == -1) {
        perror("Error during creating file");
        exit(EXIT_FAILURE);
    }
    
    printf("file was opened\n");

    while(true) {    
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    
        if (bytes_read == -1) {
            perror("Error during reading file");
            exit(EXIT_FAILURE);
        }
        if (bytes_read == 0) break;
     
        buffer[bytes_read] = '\0';
        printf("\n%s\n", buffer);
    }

    close(fd);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        // std::cerr << "Error: No file paht provided." <<std::endl;
        perror("Error: No file paht provided.");
        return 1;
    }
    //std::string filePath = argv[1];
    readFile(argv[1]);
    return 0;
}

