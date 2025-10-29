#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//non-preemptive
struct Process {
    int pid;       // Process ID
    int arrival;   // Arrival time
    int burst;     // Burst time
    int start;     // Start time
    int finish;    // Finish time
    int waiting;   // Waiting time
    int turnaround; // Turnaround time
    bool completed; // process completed?
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    //defining arrival time of each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for process " <<i+1<< ": ";
        cin >> processes[i].arrival;
    }
    //defining burst time of each process
    for (int i = 0; i < n; i++) {
        cout << "Enter burst time for process " <<i+1<< ": ";
        cin >> processes[i].burst;
        processes[i].completed = false;
    }

    int time_passed = 0, completed_count = 0;
    float total_waiting = 0, total_turnaround = 0;

    while (completed_count < n) {
        int idx = -1;
        int min_burst = 1e9;
        // minimum burst time among those that have arrived and are not completed
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= time_passed) {
                if (processes[i].burst < min_burst) {
                    min_burst = processes[i].burst;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            // koi process nahi aaya, move time forward
            time_passed++;
            continue;
        }

        // Assign times
        processes[idx].start = time_passed;
        processes[idx].finish = processes[idx].start + processes[idx].burst;
        processes[idx].turnaround = processes[idx].finish - processes[idx].arrival;
        processes[idx].waiting = processes[idx].start - processes[idx].arrival;
        total_waiting += processes[idx].waiting;
        total_turnaround += processes[idx].turnaround;

        processes[idx].completed = true;
        completed_count++;
        
        time_passed = processes[idx].finish;
    }

    cout << "\nProcess\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n";
    for (const auto &p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.start << "\t" << p.finish << "\t" << p.waiting << "\t"
             << p.turnaround << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_waiting / n<<endl;
    // cout << "\nAverage Turnaround Time: " << total_turnaround / n << endl;

    return 0;
}