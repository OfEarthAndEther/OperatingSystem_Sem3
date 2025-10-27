// Peterson's Algorithm Implementation in C++ (using threads)
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> flag[2]; // flag for each process
std::atomic<int> turn;     // whose turn is it
int shared_data = 0;       // critical section resource

void process(int id) {
    int other = 1 - id;
    for (int i = 0; i < 5; ++i) {
        // Entry section
        flag[id] = true;
        turn = other;
        while (flag[other] && turn == other) {
            // busy wait (spin)
        }

        // Critical section
        std::cout << "Process " << id << " entering critical section." << std::endl;
        shared_data += 1;
        std::cout << "Process " << id << " shared_data: " << shared_data << std::endl;
        std::cout << "Process " << id << " exiting critical section.\n" << std::endl;

        // Exit section
        flag[id] = false;

        // Remainder section
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    flag[0] = flag[1] = false;
    turn = 0;

    std::thread t1(process, 0);
    std::thread t2(process, 1);

    t1.join();
    t2.join();

    std::cout << "Final shared_data: " << shared_data << std::endl;

    return 0;
}