#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> pages = {1, 2, 3, 2, 4, 1, 5, 2};
    int capacity = 3, faults = 0;
    vector<int> frame;

    for (int i = 0; i < pages.size(); i++) {
        int p = pages[i];
        if (find(frame.begin(), frame.end(), p) == frame.end()) {
            if (frame.size() == capacity) {
                int farthest = i + 1, idx = -1;
                for (int j = 0; j < frame.size(); j++) {
                    int k = i + 1;
                    while (k < pages.size() && pages[k] != frame[j]) k++;
                    if (k > farthest) {
                        farthest = k;
                        idx = j;
                    }
                }
                if (idx == -1) frame[0] = p;
                else frame[idx] = p;
            } else {
                frame.push_back(p);
            }
            faults++;
        }
    }
    cout << "Optimal Page Faults: " << faults << endl;
    return 0;
}