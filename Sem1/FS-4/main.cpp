#include <iostream>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


void initialize(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "One argument with filepath must be provided" << std::endl;
		exit(EXIT_FAILURE);
	}

	int fd = open(argv[1], O_RDONLY);

	if (fd == -1) {
		std::cerr << "Error reading file" << std::endl;
		exit(EXIT_FAILURE);
	}

	dup2(fd, 0);
}


int main(int argc, char** argv) {
	initialize(argc, argv);
	
	std::string input;
	std::cin >> input;
	
	std::string reversed = input;
	std::reverse(reversed.begin(), reversed.end());
	
	std::cout << reversed << std::endl;
}
