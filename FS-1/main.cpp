#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void readFile(char* filePath) {
    // do smth...
    int fd = open(filePath, O_RDONLY);
    if (fd == -1) {
        perror("Error during creating file");
        exit(EXIT_FAILURE);
    }
    
    printf("file was opened\n");
    
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

