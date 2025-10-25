#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    cout<<"This will be printed but after this line next line will not be printed since it's defined after exit() statement. \n";
    cout << "Process will exit now." << endl;
    exit(0);
    cout << "This will not be printed." << endl;
}