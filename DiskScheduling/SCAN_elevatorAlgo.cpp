#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53, disk_size = 200, total = 0;
    sort(requests.begin(), requests.end());

    auto it = lower_bound(requests.begin(), requests.end(), head);
    for (auto i = it; i != requests.end(); ++i) {
        total += abs(head - *i);
        head = *i;
    }
    total += abs(head - (disk_size - 1));
    head = disk_size - 1;
    for (auto i = it - 1; i >= requests.begin(); --i) {
        total += abs(head - *i);
        head = *i;
    }

    cout << "Total SCAN head movement: " << total << endl;
    return 0;
}