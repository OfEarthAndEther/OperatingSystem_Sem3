#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int burst[n];           // Burst time for each process
    int waiting[n];         // Waiting time for each process
    int turnaround[n];      // Turnaround time for each process
    int pid[n];             // Process ID

    // Input burst times
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter burst time for process " << pid[i] << ": ";
        cin >> burst[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (burst[j] > burst[j + 1]) {
                // Swap burst times
                int temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;
                // Swap process IDs
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    // Calculate waiting and turnaround time
    waiting[0] = 0; // First process has 0 waiting time
    for (int i = 1; i < n; i++) {
        waiting[i] = waiting[i - 1] + burst[i - 1];
    }
    for (int i = 0; i < n; i++) {
        turnaround[i] = waiting[i] + burst[i];
    }

    // Output results
    cout << "\nProcess\tBurst\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t" << burst[i] << "\t" << waiting[i] << "\t" << turnaround[i] << "\n";
    }

    return 0;
}