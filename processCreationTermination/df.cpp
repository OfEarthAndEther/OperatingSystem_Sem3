#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    execl("/bin/df", "df", "-h", (char *)NULL);
    cout << "df failed." << endl;
    return 0;
}