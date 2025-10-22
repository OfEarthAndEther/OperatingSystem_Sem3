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
    int turnaround;// Turnaround time
    bool completed;// Has process completed?
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival;
    }
    for (int i = 0; i < n; i++) {
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst;
        processes[i].completed = false;
    }

    int time_passed = 0, completed_count = 0;
    float total_waiting = 0, total_turnaround = 0;

    // SJF non-preemptive main loop
    while (completed_count < n) {
        int idx = -1;
        int min_burst = 1e9;
        // Find the process with minimum burst time among those that have arrived and are not completed
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= time_passed) {
                if (processes[i].burst < min_burst) {
                    min_burst = processes[i].burst;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            // No process has arrived; move time forward
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
        // Mark as completed
        processes[idx].completed = true;
        completed_count++;
        // Move clock forward
        time_passed = processes[idx].finish;
    }

    cout << "\nProcess\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n";
    for (const auto &p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.start << "\t" << p.finish << "\t" << p.waiting << "\t"
             << p.turnaround << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_waiting / n;
    cout << "\nAverage Turnaround Time: " << total_turnaround / n << endl;

    return 0;
}


// #include <iostream>
// using namespace std;

// int main(){
//     int n;
//     cout<<"Enter the number of Processes: ";
//     cin>>n;
//     int arrival[n];
//     cout<<"Enter the arrival time for each process respectively.(in ms)";
//     for(int i=0; i<n; i++){
//         cin>>arrival[i];
//     }// abhi ke liye assuming ki 1st/ ya koi bhi ek process 0ms par aaya (nahi toh sabse choti arrival time ki value ko saari values se minus karke fir calc karte below algo se and final ans report karne par jaha jaha add karna hota kar dete.)
//     int burst[n];
//     cout<<"Enter the burst time for each process respectively.(in ms)";
//     for(int i=0; i<n; i++){
//         cin>>burst[i];
//     }
// // yaha tak hamare pass abhi saari values jo question mai given hongi wo aayi hai.
//     int time_passed=0, smol=burst[0];
//     int copy[n], termination_time[n], starting_time[n];
//     float avg_wt=0, tot_wt=0, waiting_time[n];
//     //burst array copy kiya
//     for(int i=0; i<n; i++){
//         copy[i]=burst[i];//same mai changes isliye nahikar rahe taaki changes dekh paye positions ka from original given array
//     }
//     //bubble sort implement kiya
//     for(int i=0; i<n; i++){
//         for(int j=0; j<n-1; j++){
//             if(copy[j]>copy[j+1]){
//                 int temp=copy[j];
//                 copy[j]=copy[j+1];
//                 copy[j+1]=temp;
//             }
//         }
//     }
//     //copied array se original array mai change of place dekh kar index ki array bankar save point ki tarah rakho and calculate aage ka sab kuch as it is. last mai bas ans show karte waqt save points ko refer karo.
//     for(int j=0; j<n; j++){
//         if (time_passed < arrival[j]) {
//             time_passed = arrival[j];  // CPU waits till process arrives
//         }
//         //sort(arrival time values) again assuming ki sorted order mai hi hai given
//         starting_time[j]=time_passed;
//         time_passed+=burst[j];
//         termination_time[j]=time_passed;
//         waiting_time[j] = starting_time[j] - arrival[j];
//     }
//     for(int j=0; j<n; j++){
//         tot_wt+=waiting_time[j];
//     }
//     avg_wt=tot_wt/n;
//     cout<<"The waiting time of each process is as follows: ";
//     for(int j=0; j<n; j++){
//         cout<<waiting_time[j]<<endl;
//     }
//     cout<<endl;
//     cout<<"The avg waiting time is: "<< avg_wt<< endl;


//     return 0;
// }