#include <iostream>
using namespace std;

// System parameters
const int n = 5; // number of processes (threads)
const int m = 3; // number of resource types

int Allocation[n][m] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 3},
    {2, 1, 1},
    {0, 0, 2}
};

int Request[n][m] = { // "Need" matrix: what each process still wants
    {0, 0, 0},
    {2, 0, 2},
    {0, 0, 0},
    {1, 0, 0},
    {0, 0, 2}
};

int Available[m] = {0, 0, 0}; // resources available of each type

void deadlockDetection() {
    bool Finish[n];
    int Work[m];
    for (int i = 0; i < m; ++i) Work[i] = Available[i];
    for (int i = 0; i < n; ++i) {
        bool isZero = true;
        for (int j = 0; j < m; ++j)
            if (Allocation[i][j] != 0) isZero = false;
        Finish[i] = isZero;
    }

    bool progress = true;
    while (progress) {
        progress = false;
        for (int i = 0; i < n; ++i) {
            if (!Finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < m; ++j) {
                    if (Request[i][j] > Work[j]) { // cannot satisfy
                        canProceed = false;
                        break;
                    }
                }
                if (canProceed) {
                    // "Complete" this process: release allocation
                    for (int k = 0; k < m; ++k)
                        Work[k] += Allocation[i][k];
                    Finish[i] = true;
                    progress = true;
                }
            }
        }
    }

    // Print deadlocked threads
    bool deadlock = false;
    for (int i = 0; i < n; ++i) {
        if (!Finish[i]) {
            deadlock = true;
            cout << "Thread T" << i << " is deadlocked." << endl;
        }
    }
    if (!deadlock)
        cout << "No deadlock detected. System is safe." << endl;
}

int main() {
    deadlockDetection();
    return 0;
}