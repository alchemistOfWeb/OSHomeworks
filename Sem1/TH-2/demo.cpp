#include "parallelScheduler.h"
#include <iostream>
#include <unistd.h> // For sleep

void sampleFunction(void* arg) {
    int taskId = *static_cast<int*>(arg);
    std::cout << "Task " << taskId << " is starting..." << std::endl;
    sleep(1);
    std::cout << "Task " << taskId << " is done." << std::endl;
}

int main() {
    const int poolCapacity = 3;
    const int taskCount = 10;
    parallelScheduler scheduler(poolCapacity);

    for (int i = 0; i < taskCount; ++i) {
        int* taskId = new int(i);
        scheduler.run(sampleFunction, taskId);
    }

    sleep(5); // Wait for tasks to complete
    return 0;
}

