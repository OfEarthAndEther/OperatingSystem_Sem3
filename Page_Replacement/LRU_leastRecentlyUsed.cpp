#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> pages = {1, 2, 3, 2, 4, 1, 5, 2};
    int capacity = 3, faults = 0;
    vector<int> frame;

    for (int p : pages) {
        auto it = find(frame.begin(), frame.end(), p);
        if (it == frame.end()) {
            if (frame.size() == capacity)
                frame.erase(frame.begin());
            faults++;
        } else {
            frame.erase(it);
        }
        frame.push_back(p);
    }
    cout << "LRU Page Faults: " << faults << endl;
    return 0;
}