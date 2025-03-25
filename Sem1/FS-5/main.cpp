#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv) {
	if (argc < 2) {
		perror("There must be provided one argument");
		exit(EXIT_FAILURE);
	}

	char* filepath = argv[1];
	int fd1 = open(filepath, O_WRONLY | O_CREAT, 777);

	if (fd1 == -1) {
		perror("Error during opening file");
		exit(EXIT_FAILURE);
	}
	
	const char* str1 = "first line\n";
	write(fd1, str1, strlen(str1));

	int fd2 = dup(fd1);
	const char* str2 = "second line\n";
	write(fd2, str2, strlen(str2));
	
	close(fd1);
	close(fd2);
	return 0;
}
