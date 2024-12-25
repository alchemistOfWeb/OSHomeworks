#pragma once

#include <pthread.h>
#include <queue>
#include <functional>
#include <vector>

class parallelScheduler {
public:
    explicit parallelScheduler(size_t capacity);
    ~parallelScheduler();

    void run(std::function<void(void*)> func, void* arg);

private:
    static void* workerThread(void* arg);

    size_t maxThreads;
    std::vector<pthread_t> threads;
    std::queue<std::function<void()>> taskQueue;
    pthread_mutex_t queueMutex;
    pthread_cond_t condition;
    bool stop;
};


