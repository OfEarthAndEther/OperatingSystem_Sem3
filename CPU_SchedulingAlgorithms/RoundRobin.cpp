#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// Round Robin is inherently Preemptive
struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time (original)
    int remaining;   // Remaining burst time
    int finish;      // Completion (exit) time
    int waiting;     // Waiting time
    int turnaround;  // Turnaround time
};

int main() {
    int n, quantum;
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
    }
    cout << "Enter time quantum: ";
    cin >> quantum;

    queue<int> ready; // Indices of processes ready to execute
    int time = 0, completed = 0;
    vector<bool> queued(n, false);

    // Initial population of ready queue
    for (int i = 0; i < n; ++i)
        if (p[i].arrival <= time && !queued[i])
            ready.push(i), queued[i] = true;

    while (completed < n) {
        if (ready.empty()) {
            // Find next earliest arriving process
            int min_arr = 1e9, idx = -1;
            for (int i = 0; i < n; ++i)
                if (!queued[i] && p[i].arrival < min_arr) {
                    min_arr = p[i].arrival;
                    idx = i;
                }
            time = min_arr;
            ready.push(idx);
            queued[idx] = true;
        }
        int idx = ready.front();
        ready.pop();

        int exec_time = min(quantum, p[idx].remaining);
        // Actual processing
        time = max(time, p[idx].arrival); // CPU waits if idle
        p[idx].remaining -= exec_time;
        time += exec_time;

        // Push newly arrived processes to queue
        for (int i = 0; i < n; ++i)
            if (!queued[i] && p[i].arrival <= time) {
                ready.push(i);
                queued[i] = true;
            }

        if (p[idx].remaining == 0) {
            p[idx].finish = time;
            ++completed;
        } else {
            ready.push(idx); // unfinished, goes to end of queue
        }
    }
    float total_waiting = 0, total_turnaround = 0;
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