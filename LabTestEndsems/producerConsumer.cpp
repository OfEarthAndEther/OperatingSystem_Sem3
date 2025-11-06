#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <ctime>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;

std::mutex mutex;
std::condition_variable not_full;
std::condition_variable not_empty;

// Producer function
void producer() {
    while (true) {
        int item = rand() % 100; // produce an item

        std::unique_lock<std::mutex> lock(mutex);
        not_full.wait(lock, [] { return count < BUFFER_SIZE; });

        buffer[in] = item;
        std::cout << "Produced: " << item << " at " << in << std::endl;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        not_empty.notify_one(); // signal buffer has item

        std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate production time
    }
}

// Consumer function
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex);
        not_empty.wait(lock, [] { return count > 0; });

        int item = buffer[out];
        std::cout << "Consumed: " << item << " at " << out << std::endl;
        out = (out + 1) % BUFFER_SIZE;
        count--;

        not_full.notify_one(); // signal buffer has space

        std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate consumption time
    }
}

int main() {
    std::srand(std::time(0));
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    return 0;
}