#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53, total = 0;
    vector<bool> visited(requests.size(), false);

    for (int i = 0; i < requests.size(); i++) {
        int minDist = 1e9, idx = -1;
        for (int j = 0; j < requests.size(); j++) {
            if (!visited[j] && abs(head - requests[j]) < minDist) {
                minDist = abs(head - requests[j]);
                idx = j;
            }
        }
        total += minDist;
        head = requests[idx];
        visited[idx] = true;
    }

    cout << "Total SSTF head movement: " << total << endl;
    return 0;
}