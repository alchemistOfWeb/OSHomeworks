#include "parallelScheduler.h"
#include <iostream>

parallelScheduler::parallelScheduler(size_t capacity) : maxThreads(capacity), stop(false) {
    pthread_mutex_init(&queueMutex, nullptr);
    pthread_cond_init(&condition, nullptr);

    for (size_t i = 0; i < maxThreads; ++i) {
        pthread_t thread;
        pthread_create(&thread, nullptr, workerThread, this);
        threads.push_back(thread);
    }
}

parallelScheduler::~parallelScheduler() {
    pthread_mutex_lock(&queueMutex);
    stop = true;
    pthread_cond_broadcast(&condition);
    pthread_mutex_unlock(&queueMutex);

    for (auto& thread : threads) {
        pthread_join(thread, nullptr);
    }

    pthread_mutex_destroy(&queueMutex);
    pthread_cond_destroy(&condition);
}

void parallelScheduler::run(std::function<void(void*)> func, void* arg) {
    pthread_mutex_lock(&queueMutex);
    taskQueue.push([=]() { func(arg); });
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&queueMutex);
}

void* parallelScheduler::workerThread(void* arg) {
    auto* scheduler = static_cast<parallelScheduler*>(arg);

    while (true) {
        std::function<void()> task;

        pthread_mutex_lock(&scheduler->queueMutex);
        while (scheduler->taskQueue.empty() && !scheduler->stop) {
            pthread_cond_wait(&scheduler->condition, &scheduler->queueMutex);
        }

        if (scheduler->stop && scheduler->taskQueue.empty()) {
            pthread_mutex_unlock(&scheduler->queueMutex);
            return nullptr;
        }

        task = std::move(scheduler->taskQueue.front());
        scheduler->taskQueue.pop();
        pthread_mutex_unlock(&scheduler->queueMutex);

        task();
    }
}

