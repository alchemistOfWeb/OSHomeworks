#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define BUFFER_SIZE 1024
#define INVALID_FD -1


void copyFile(char* source, char* dest) {
    int srcFD = open(source, O_RDONLY);
   
    int destFD = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (srcFD == INVALID_FD || destFD == INVALID_FD) {
        perror("Error during opening file");
        exit(EXIT_FAILURE);
    }
 
    while(true) {    
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read = read(srcFD, buffer, sizeof(buffer) - 1);
    
        if (bytes_read == -1) {
            perror("Error during reading file");
            exit(EXIT_FAILURE);
        }
        if (bytes_read == 0) break;
     
        buffer[bytes_read] = '\0';
        write(destFD, buffer, strlen(buffer));
    }
    close(srcFD);
    close(destFD);
}


int main(int argc, char** argv) {
    if (argc < 3) {
        perror("Error: there must be 2 arguments");
        exit(EXIT_FAILURE);
    }

    copyFile(argv[1], argv[2]);
    return 0;
}

