#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>

#define NUM_PHILOSOPHERS 5

sem_t *stick[NUM_PHILOSOPHERS];
const char *sem_names[] = {"/stick0", "/stick1", "/stick2", "/stick3", "/stick4"};


void philosopher(int id) {
    srand(time(NULL) ^ getpid());

    while (true) {
        int think_time = rand() % 3 + 1;
        printf("Philosopher %d: Thinking for %d sec...\n", id, think_time);
        sleep(think_time);

        if (id == NUM_PHILOSOPHERS - 1) {  
            sem_wait(stick[(id + 1) % NUM_PHILOSOPHERS]); 
            printf("Philosopher %d: Picked up right chopstick\n", id);

            sem_wait(stick[id]);
            printf("Philosopher %d: Picked up left chopstick\n", id);
        } else {
            sem_wait(stick[id]);
            printf("Philosopher %d: Picked up left chopstick\n", id);

            sem_wait(stick[(id + 1) % NUM_PHILOSOPHERS]);
            printf("Philosopher %d: Picked up right chopstick\n", id);
        }

        int eat_time = rand() % 3 + 1;
        printf("Philosopher %d: Eating for %d sec...\n", id, eat_time);
        sleep(eat_time);

        sem_post(stick[id]);
        sem_post(stick[(id + 1) % NUM_PHILOSOPHERS]); 
        printf("Philosopher %d: Put down both chopsticks\n", id);
    }
}

int main() {
    pid_t pids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        stick[i] = sem_open(sem_names[i], O_CREAT, 0666, 1);
        if (stick[i] == SEM_FAILED) {
            perror("error during opening named semaphore");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            philosopher(i);
            exit(0);
        } else if (pids[i] < 0) {
            perror("error during fork process");
            exit(EXIT_FAILURE);
        }
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        wait(NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_close(stick[i]);
        sem_unlink(sem_names[i]);
    }

    return 0;
}
