#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void handler(int sig) {
    cout << "Signal caught: " << sig << endl;
    exit(0); // terminate gracefully
}

int main() {
    signal(SIGINT, handler);
    cout << "Waiting for Ctrl+C (SIGINT)..." << endl;
    while (1)
        sleep(1);
    return 0;
}