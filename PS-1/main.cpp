#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


void do_command(char** argv) {
	clock_t begin = clock();

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork error");
        return;
    }

    if (pid == 0) { // parent process
        execvp(argv[0], argv);
        perror("Error during executing command"); 
        exit(EXIT_FAILURE);
    } else { // child process
        int status;
        waitpid(pid, &status, 0);

        double duration = ((double)(clock() - begin)) / CLOCKS_PER_SEC;

        if (WIFEXITED(status)) {
            printf("Completed with %d exit code and took %.2f seconts\n", WEXITSTATUS(status), duration);
        } else {
            printf("Completed with some errors.\n");
        }
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        perror("Corrects usage: ./do-command <command> [arguments...]\n");
        exit(EXIT_FAILURE);
    }

    do_command(argv + 1); // pass arguments wihtout program name
    return 0;
}

