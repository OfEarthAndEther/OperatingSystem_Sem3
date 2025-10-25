// 7. du: shows disk usage
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    execl("/usr/bin/du", "du", "-h", ".", (char *)NULL);
    cout << "du failed." << endl;
    return 0;
}