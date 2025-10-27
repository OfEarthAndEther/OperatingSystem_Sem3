#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable not_empty;

void producer(int items) {
    for (int i = 1; i <= items; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            buffer.push(i);
            std::cout << "Produced: " << i << " (Buffer size: " << buffer.size() << ")" << std::endl;
        }
        not_empty.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(int items) {
    for (int i = 1; i <= items; ++i) {
        int item = -1;
        {
            std::unique_lock<std::mutex> lock(mtx);
            not_empty.wait(lock, []{ return !buffer.empty(); });
            item = buffer.front();
            buffer.pop();
            std::cout << "Consumed: " << item << " (Buffer size: " << buffer.size() << ")" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main() {
    int N = 15;
    std::thread prod(producer, N);
    std::thread cons(consumer, N);
    prod.join();
    cons.join();
    return 0;
}