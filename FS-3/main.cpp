#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/stat.h>

#define BUFFER_SIZE 4096
#define INVALID_FD -1

off_t getFileSize(int fd) {
    //struct stat st;
    //if (fstat(fd, &st) !=0) {
    //    perror("Error during checking size of file");
    //    close(fd);
    //    exit(EXIT_FAILURE);
    // }
    return lseek(fd, 0, SEEK_END);
    // return st.st_size;
}

void secureDelete(char* source) {
    int srcFD = open(source, O_WRONLY);
   
    if (srcFD == INVALID_FD) {
        perror("Error during opening file");
        exit(EXIT_FAILURE);
    }

    off_t fileSize = getFileSize(srcFD);
    off_t counter = 0;
    
    char buffer[BUFFER_SIZE];
    for (int i=0; i<BUFFER_SIZE; i++) {
        buffer[i] = '\0';
    }
    printf("file size %ld", fileSize);

    do {
        if(fileSize == 0) break;
   
        ssize_t bytes_write = write(srcFD, buffer, strlen(buffer));
 
        if (bytes_write == -1) {
            perror("Error during writing into file");
            exit(EXIT_FAILURE);
        }

    } while((counter += BUFFER_SIZE) <= fileSize);

    close(srcFD);
    if (unlink(source) != 0) {
        perror("Error during unlinking file");
        exit(EXIT_FAILURE);
    }

}


int main(int argc, char** argv) {
    if (argc < 2) {
        perror("Error: filepath was not provided");
        exit(EXIT_FAILURE);
    }

    secureDelete(argv[1]);
    return 0;
}

