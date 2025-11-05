#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int main() {
    vector<int> pages = {1, 2, 3, 2, 4, 1, 5, 2};
    int capacity = 3, faults = 0;
    queue<int> q;
    unordered_set<int> s;

    for (int p : pages) {
        if (s.find(p) == s.end()) {
            if (q.size() == capacity) {
                s.erase(q.front());
                q.pop();
            }
            q.push(p);
            s.insert(p);
            faults++;
        }
    }
    cout << "FIFO Page Faults: " << faults << endl;
    return 0;
}


// #include <iostream>
// #include <queue>
// #include <unordered_set>
// using namespace std;

// int main() {
//     int n, frames;
//     cout << "Enter number of pages: ";
//     cin >> n;
//     int pages[n];
//     cout << "Enter page sequence: ";
//     for (int i = 0; i < n; i++) cin >> pages[i];
//     cout << "Enter number of frames: ";
//     cin >> frames;

//     unordered_set<int> s;
//     queue<int> q;
//     int faults = 0;
//     for (int i = 0; i < n; i++) {
//         if (s.size() < frames && s.find(pages[i]) == s.end()) {
//             s.insert(pages[i]);
//             q.push(pages[i]);
//             faults++;
//         } else if (s.find(pages[i]) == s.end()) {
//             int oldest = q.front();
//             q.pop();
//             s.erase(oldest);
//             s.insert(pages[i]);
//             q.push(pages[i]);
//             faults++;
//         }
//     }
//     cout << "FIFO Page Faults: " << faults << endl;
//     return 0;
// }