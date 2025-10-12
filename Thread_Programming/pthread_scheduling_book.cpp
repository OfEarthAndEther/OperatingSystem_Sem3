//This file contained book C code converted to C++ code for p thread execution initially
//Then commenting that we wrote a better code. // small addition for understanding threading in action. print each thread’s ID (so you can visually see them running concurrently). But that did not have proper printing features due to which there was a glitch in the display output..like process 1 2 2 3 only and not all processes in the range...// pitfall description: threads share the same memory address for i. By the time each thread starts running, the loop might have already incremented i several times.
//final code has all glitches fixed.

#include <iostream>
#include <pthread.h>
#define NUM_THREADS 5

void* runner(void* param);

int main() {
    int i, scope;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;

    // Initialize thread attributes
    pthread_attr_init(&attr);

    // Get the current scheduling scope
    if (pthread_attr_getscope(&attr, &scope) != 0)
        std::cerr << "Unable to get scheduling scope\n";
    else {
        if (scope == PTHREAD_SCOPE_PROCESS)
            std::cout << "Current Scope: PTHREAD_SCOPE_PROCESS\n";
        else if (scope == PTHREAD_SCOPE_SYSTEM)
            std::cout << "Current Scope: PTHREAD_SCOPE_SYSTEM\n";
        else
            std::cerr << "Illegal scope value.\n";
    }

    // Set the scheduling scope to SYSTEM
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    std::cout << "\nCreating " << NUM_THREADS << " threads...\n";

    // Create threads with unique argument
    for (i = 0; i < NUM_THREADS; i++) {
        int* threadNum = new int(i);  // unique copy of i
        pthread_create(&tid[i], &attr, runner, threadNum);
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], nullptr);
    }

    std::cout << "\nAll threads have finished execution.\n";
    return 0;
}

// Thread function
void* runner(void* param) {
    int threadNum = *(int*)param; // Get thread number safely
    std::cout << "Thread " << threadNum 
              << " is running. Thread ID: " << pthread_self() << "\n";

    delete (int*)param; // Free allocated memory
    pthread_exit(0);
}


// #include <iostream>
// #include <pthread.h>
// #define NUM_THREADS 5

// void* runner(void* param);

// int main() {
//     int i, scope;
//     pthread_t tid[NUM_THREADS];
//     pthread_attr_t attr;

//     // Initialize thread attributes
//     pthread_attr_init(&attr);

//     // Get the current scheduling scope
//     if (pthread_attr_getscope(&attr, &scope) != 0)
//         std::cerr << "Unable to get scheduling scope\n";
//     else {
//         if (scope == PTHREAD_SCOPE_PROCESS)
//             std::cout << "Current Scope: PTHREAD_SCOPE_PROCESS\n";
//         else if (scope == PTHREAD_SCOPE_SYSTEM)
//             std::cout << "Current Scope: PTHREAD_SCOPE_SYSTEM\n";
//         else
//             std::cerr << "Illegal scope value.\n";
//     }

//     // Set the scheduling scope to SYSTEM
//     pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

//     std::cout << "\nCreating " << NUM_THREADS << " threads...\n";

//     // Create the threads
//     for (i = 0; i < NUM_THREADS; i++) {
//         pthread_create(&tid[i], &attr, runner, (void*)&i);
//     }

//     // Wait for all threads to finish
//     for (i = 0; i < NUM_THREADS; i++) {
//         pthread_join(tid[i], nullptr);
//     }

//     std::cout << "\nAll threads have finished execution.\n";
//     return 0;
// }

// // Thread function
// void* runner(void* param) {
//     int threadNum = *(int*)param; // Get the thread number
//     std::cout << "Thread " << threadNum << " is running. Thread ID: "
//               << pthread_self() << "\n";

//     // Simulate work
//     pthread_exit(0);
// }


// // #include <iostream>
// // #include <pthread.h>
// // #define NUM_THREADS 5

// // // Thread function prototype
// // void* runner(void* param);

// // int main() {
// //     int i, scope;
// //     pthread_t tid[NUM_THREADS];
// //     pthread_attr_t attr;

// //     // Get the default attributes
// //     pthread_attr_init(&attr);

// //     // First inquire about the current scope
// //     if (pthread_attr_getscope(&attr, &scope) != 0)
// //         std::cerr << "Unable to get scheduling scope\n";
// //     else {
// //         if (scope == PTHREAD_SCOPE_PROCESS)
// //             std::cout << "PTHREAD_SCOPE_PROCESS\n";
// //         else if (scope == PTHREAD_SCOPE_SYSTEM)
// //             std::cout << "PTHREAD_SCOPE_SYSTEM\n";
// //         else
// //             std::cerr << "Illegal scope value.\n";
// //     }

// //     // Set the scheduling scope to SYSTEM
// //     pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

// //     // Create the threads
// //     for (i = 0; i < NUM_THREADS; i++)
// //         pthread_create(&tid[i], &attr, runner, nullptr);

// //     // Join each thread
// //     for (i = 0; i < NUM_THREADS; i++)
// //         pthread_join(tid[i], nullptr);

// //     return 0;
// // }

// // // Each thread begins execution here
// // void* runner(void* param) {
// //     // Do some work here
// //     pthread_exit(0);
// // }