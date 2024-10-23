#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


void execute_command(char* command, int silent) {
    char* argv[100];
    int i = 0;
    char* token = strtok(command, " ");
    while (token != NULL && i < 99) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;  

    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed to fork");
        return;
    }

    if (pid == 0) { // child process
        if (silent) {
            // Redirect stdout and stderr to PID.log
            char log_file[50];
            sprintf(log_file, "%d.log", getpid());
            int log_fd = open(log_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (log_fd < 0) {
                perror("Failed to open log file");
                exit(EXIT_FAILURE);
            }
            dup2(log_fd, STDOUT_FILENO);  
            dup2(log_fd, STDERR_FILENO); 
            close(log_fd);
        }

        char* path = getenv("PATH");
        char new_path[1024];
        snprintf(new_path, sizeof(new_path), "./:%s", path);
        setenv("PATH", new_path, 1);
		
		if (execvp(argv[0], argv) == -1) {
    		perror("Error during executing command");
    		exit(EXIT_FAILURE);
		}
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Command completed with exit code %d\n", WEXITSTATUS(status));
        } else {
            printf("Command completed with some errorrs.\n");
        }
    }
}

int main() {
    char command[1024];

    while (true) {
        printf(">>> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; 
        }

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell.\n");
            break;
        }

        int silent = 0;
        if (strncmp(command, "silent ", 7) == 0) {
            silent = 1;
            memmove(command, command + 7, strlen(command) - 6);  
        }

        execute_command(command, silent);
    }

    return 0;
}

