#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <ctime>
#include <vector>
#include <iostream>


pthread_mutex_t mutex;
long long totalSum = 0;

struct ThreadData {
    const std::vector<int>* arr;
    long long start;
    long long end;
};

double get_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec + time.tv_usec / 1e6;
}

void* thread_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long localSum = 0;

    for (long long i = data->start; i < data->end; ++i) {
        localSum += (*(data->arr))[i];
    }

    pthread_mutex_lock(&mutex);
    totalSum += localSum;
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Corrects usage: <N: size of array> <M: number of threads>\n");
        exit(EXIT_FAILURE);
    }
	
	long long arrayLen = std::stoll(argv[1]);
	long threadsNum = std::stoi(argv[2]);

	std::vector<int> arr(arrayLen);
	std::srand(time(NULL));

	for(long long i=0; i < arrayLen; i++) {
		arr[i] = std::rand() % 100;
	}

	// SINGLE THREAD SUM
	long long singleThreadSum = 0;
	double startTime = get_time();

	for(long long i=0; i < arrayLen; i++) {
		singleThreadSum += arr[i];
	}

	std::cout << "time spend with one thread: " << get_time() - startTime << std::endl;
	
	// MULTITHREADING
	pthread_mutex_init(&mutex, nullptr);
	long long totalSum = 0;
	std::vector<pthread_t> threads(threadsNum);
	std::vector<ThreadData> threadData(threadsNum);

	long long chunkSize = arrayLen / threadsNum;
	
	startTime = get_time();

	for(int i = 0; i < threadsNum; ++i) {
		threadData[i].arr = &arr;
		threadData[i].start = i * chunkSize;
		threadData[i].end = (i == threadsNum - 1) ? arrayLen : (i + 1) * chunkSize;

		pthread_create(&threads[i], nullptr, thread_sum, &threadData[i]);
	}

	for(int i = 0; i < threadsNum; ++i) {
		pthread_join(threads[i], nullptr);
	}
	
	std::cout << "time spend with multythreading: " << get_time() - startTime << std::endl;

	pthread_mutex_destroy(&mutex);

    return 0;
}

