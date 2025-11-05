#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream file("example.txt"); // open/create
    file << "Hello OS Lab!\n";    // write
    file.close();                 // close
    cout << "File written and closed.\n";
    return 0;
}