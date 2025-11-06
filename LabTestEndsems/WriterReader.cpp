#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore.h>

sem_t mutex, wrt;
int readcount = 0;

void reader(int id) {
    for (int j = 0; j < 3; ++j) {
        sem_wait(&mutex);
        ++readcount;
        if (readcount == 1)
            sem_wait(&wrt); // first reader blocks writers
        sem_post(&mutex);

        // CRITICAL SECTION
        std::cout << "Reader " << id << " is reading.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        sem_wait(&mutex);
        --readcount;
        if (readcount == 0)
            sem_post(&wrt); // last reader unblocks writers
        sem_post(&mutex);

        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // remainder section
    }
}

void writer(int id) {
    for (int j = 0; j < 2; ++j) {
        sem_wait(&wrt);
        // CRITICAL SECTION
        std::cout << "Writer " << id << " is writing.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        sem_post(&wrt);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // remainder
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    std::vector<std::thread> readers, writers;
    for (int i = 1; i <= 4; ++i)
        readers.emplace_back(reader, i);
    for (int i = 1; i <= 2; ++i)
        writers.emplace_back(writer, i);

    for (auto& r : readers) r.join();
    for (auto& w : writers) w.join();

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}