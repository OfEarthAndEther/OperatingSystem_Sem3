#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53, total = 0;

    for (int r : requests) {
        total += abs(head - r);
        head = r;
    }

    cout << "Total FCFS head movement: " << total << endl;
    return 0;
}