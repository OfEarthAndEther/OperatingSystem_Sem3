#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream file("example.txt", ios::app); // open in append mode
    file << "Appended line.\n";
    file.close();
    cout << "Line appended.\n";
    return 0;
}