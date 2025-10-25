// Adding wait() to synchronize process
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0)
        cout << "Child running (PID: " << getpid() << ")" << endl;
    else {
        wait(NULL);
        cout << "Parent waited for child (PID: " << getpid() << ")" << endl;
    }
    return 0;
}