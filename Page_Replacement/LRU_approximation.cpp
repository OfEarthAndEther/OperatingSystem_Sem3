#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> pages = {1, 2, 3, 2, 4, 1, 5, 2};
    int capacity = 3, faults = 0, pointer = 0;
    vector<int> frame(capacity, -1);
    vector<bool> ref(capacity, false);

    for (int p : pages) {
        bool hit = false;
        for (int i = 0; i < capacity; i++) {
            if (frame[i] == p) {
                ref[i] = true;
                hit = true;
                break;
            }
        }
        if (!hit) {
            while (ref[pointer]) {
                ref[pointer] = false;
                pointer = (pointer + 1) % capacity;
            }
            frame[pointer] = p;
            ref[pointer] = true;
            pointer = (pointer + 1) % capacity;
            faults++;
        }
    }
    cout << "LRU-Approx Page Faults: " << faults << endl;
    return 0;
}