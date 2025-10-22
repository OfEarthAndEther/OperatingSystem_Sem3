#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time (original)
    int remaining;   // Remaining time
    int finish;      // Completion time
    int waiting;     // Waiting time
    int turnaround;  // Turnaround time
    bool completed;  // Completion flag
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> p[i].arrival;
    }
    for (int i = 0; i < n; ++i) {
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> p[i].burst;
        p[i].remaining = p[i].burst;
        p[i].completed = false;
    }

    int completed = 0, time = 0, prev = -1;
    float total_waiting = 0, total_turnaround = 0;

    while (completed < n) {
        int idx = -1, min_rem = 1e9;
        for (int i = 0; i < n; ++i) {
            if (p[i].arrival <= time && !p[i].completed && p[i].remaining < min_rem && p[i].remaining > 0) {
                min_rem = p[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) {
            // No process is ready; move time forward
            time++;
            continue;
        }

        // Run process for 1 time unit (preemption step)
        p[idx].remaining--;
        time++;

        // Check for completion
        if (p[idx].remaining == 0) {
            p[idx].finish = time;
            p[idx].completed = true;
            completed++;
        }
    }

    cout << "\nProcess\tArrival\tBurst\tFinish\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; ++i) {
        p[i].turnaround = p[i].finish - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        total_waiting += p[i].waiting;
        total_turnaround += p[i].turnaround;
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].finish << "\t" << p[i].waiting << "\t" << p[i].turnaround << "\n";
    }
    cout << "\nAverage Waiting Time: " << total_waiting / n;
    cout << "\nAverage Turnaround Time: " << total_turnaround / n << endl;
    return 0;
}