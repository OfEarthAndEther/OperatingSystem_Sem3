#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

const int BUFFER_SIZE = 5;
std::vector<int> buffer;
std::mutex mtx;
std::condition_variable not_full, not_empty;

void producer(int items) {
    for (int i = 0; i < items; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        not_full.wait(lock, []{ return buffer.size() < BUFFER_SIZE; });
        buffer.push_back(i+1);
        std::cout << "Produced: " << (i+1) << std::endl;
        lock.unlock();
        not_empty.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumer(int items) {
    for (int i = 0; i < items; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        not_empty.wait(lock, []{ return !buffer.empty(); });
        int item = buffer.front();
        buffer.erase(buffer.begin());
        std::cout << "Consumed: " << item << std::endl;
        lock.unlock();
        not_full.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
}

int main() {
    int N = 10;
    std::thread t1(producer, N);
    std::thread t2(consumer, N);
    t1.join();
    t2.join();
    return 0;
}