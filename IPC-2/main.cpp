#include <iostream>
#include <unistd.h>
#include <ctime>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include <vector>


bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}


int getPrime(int m) {
    int count = 0;
    int num = 2;
    while (count < m) {
        if (isPrime(num)) count++;
        num++;
    }
    return num - 1;
}


int main() {
    int pipeParentToChild[2], pipeChildToParent[2];

	// Create pipes
    if (pipe(pipeParentToChild) == -1 || pipe(pipeChildToParent) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork(); 

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {  // Child procss
        close(pipeParentToChild[1]);  // Close write_end of pipe
        close(pipeChildToParent[0]);  // Close read_end of pipe

        int m;
        while (true) {
            // Read the number m from the parent via pipe
            read(pipeParentToChild[0], &m, sizeof(m));

            if (m == 0) {
                break;
            }

            std::cout << "[Child] Calculating " << m << "-th prime number...\n"; 
            int prime = getPrime(m);

            // Send the result back to the parent process
            write(pipeChildToParent[1], &prime, sizeof(prime));
            std::cout << "[Child] Sending calculation result of prime(" << m << ") = " << prime << "...\n";
        }

        close(pipeParentToChild[0]);
        close(pipeChildToParent[1]);

        return 0;

    } else {  // Parent process
        close(pipeParentToChild[0]); 
        close(pipeChildToParent[1]); 

        int m;
        while (true) {
            std::cout << "[Parent] Please enter the number (or type exit or 'ctrl+C' to exit): "; // hmm
            std::string input;
            std::getline(std::cin, input);

            if (input == "exit") {
                m = 0;
                write(pipeParentToChild[1], &m, sizeof(m));
                break;
            }

            try {
                m = std::stoi(input);
                std::cout << "[Parent] Sending " << m << " to the child process...\n";

                // Send  m to child process
                write(pipeParentToChild[1], &m, sizeof(m));
                std::cout << "[Parent] Waiting for the response from the child process...\n";

                int prime;
                // Read the result from child process
                read(pipeChildToParent[0], &prime, sizeof(prime));
                std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << prime << "...\n";
            } catch (const std::exception& e) {
                std::cout << "[Parent] Invalid input. Please enter an integer.\n";
            }
        }

        close(pipeParentToChild[1]);
        close(pipeChildToParent[0]);

        wait(nullptr);
    }

    return 0;
}

