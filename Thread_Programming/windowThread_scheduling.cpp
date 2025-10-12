#include <iostream>
#include <windows.h>

#define NUM_THREADS 5

// Thread function (must match WINAPI signature)
DWORD WINAPI runner(LPVOID param) {
    int threadNum = *(int*)param;
    std::cout << "Thread " << threadNum
              << " is running. Thread ID: " << GetCurrentThreadId() << "\n";
    delete (int*)param;
    return 0;
}

int main() {
    HANDLE threads[NUM_THREADS];
    DWORD threadIds[NUM_THREADS];

    std::cout << "\nCreating " << NUM_THREADS << " threads...\n";

    // Create threads with unique argument
    for (int i = 0; i < NUM_THREADS; i++) {
        int* threadNum = new int(i);
        threads[i] = CreateThread(
            NULL,                // default security attributes
            0,                   // default stack size
            runner,              // thread function
            threadNum,           // thread argument
            0,                   // run immediately
            &threadIds[i]        // thread identifier
        );
        if (threads[i] == NULL) {
            std::cerr << "Unable to create thread " << i << "\n";
            delete threadNum;
        }
    }

    // Wait for all threads to finish
    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    // Close thread handles
    for (int i = 0; i < NUM_THREADS; i++) {
        CloseHandle(threads[i]);
    }

    std::cout << "\nAll threads have finished execution.\n";
    return 0;
}
