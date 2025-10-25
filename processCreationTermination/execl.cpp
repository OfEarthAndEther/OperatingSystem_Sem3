#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    execl("/bin/ls", "ls", "-l", (char *)NULL);
    cout << "If execl fails, this prints." << endl;
    return 0;
}