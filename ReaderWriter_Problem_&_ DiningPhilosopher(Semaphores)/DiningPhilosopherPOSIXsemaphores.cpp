#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
#include <chrono>

#define N 5

sem_t forks[N];
sem_t mutex;

void philosopher(int id) {
    for (int i = 0; i < 3; ++i) {
        // Thinking section
        std::cout << "Philosopher " << id << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Pickup forks
        sem_wait(&forks[id]);
        sem_wait(&forks[(id+1)%N]);

        // Critical section (eating)
        sem_wait(&mutex);
        std::cout << "Philosopher " << id << " is eating.\n";
        sem_post(&mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        // Put down forks
        sem_post(&forks[id]);
        sem_post(&forks[(id+1)%N]);
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; ++i)
        sem_init(&forks[i], 0, 1);

    std::vector<std::thread> philosophers;
    for (int i = 0; i < N; ++i)
        philosophers.emplace_back(philosopher, i);

    for (auto& ph : philosophers) ph.join();
    for (int i = 0; i < N; ++i)
        sem_destroy(&forks[i]);
    sem_destroy(&mutex);
    return 0;
}