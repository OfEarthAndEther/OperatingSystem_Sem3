#include <iostream>
using namespace std;

const int N_PROCESSES = 5; // Number of processes
const int N_RESOURCES = 3; // Number of resources

int finish[N_PROCESSES];
int need[N_PROCESSES][N_RESOURCES];
int maxm[N_PROCESSES][N_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allot[N_PROCESSES][N_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int avail[N_RESOURCES] = {3, 3, 2};

void calculateNeed() {
    for (int i = 0; i < N_PROCESSES; i++)
        for (int j = 0; j < N_RESOURCES; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
}

bool isSafe() {
    int work[N_RESOURCES];
    for (int i = 0; i < N_RESOURCES; i++)
        work[i] = avail[i];
    for (int i = 0; i < N_PROCESSES; i++)
        finish[i] = 0; // false

    int safeSeq[N_PROCESSES], count = 0;
    while (count < N_PROCESSES) {
        bool found = false;
        for (int p = 0; p < N_PROCESSES; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < N_RESOURCES; j++)
                    if (need[p][j] > work[j])
                        break;
                if (j == N_RESOURCES) { // If all needs are less than work
                    for (int k = 0; k < N_RESOURCES; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1; // true
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in safe state." << endl;
            return false;
        }
    }

    cout << "System is in safe state.\nSafe sequence is: ";
    for (int i = 0; i < N_PROCESSES; i++)
        cout << safeSeq[i] << " ";
    cout << endl;
    return true;
}

int main() {
    calculateNeed();
    isSafe();
    return 0;
}