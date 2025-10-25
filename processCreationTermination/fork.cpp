// 1. Using fork() to create a simple program
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0)
        cout << "Child process (PID: " << getpid() << ")" << endl;
    else
        cout << "Parent process (PID: " << getpid() << ")" << endl;

    return 0;
}