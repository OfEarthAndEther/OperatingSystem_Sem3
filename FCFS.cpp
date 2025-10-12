#include <iostream>
#include <unordered_map>
using namespace std;

int main(){
    int arr_time=0, burst_time=0;
    int query_num=0;
    cin>>query_num;
    unordered_map<int,int> process;
    for(int i=0; i<query_num; i++){
        cout<<"\nEnter arrival time of the process: \t";
        cin>>arr_time;
        cout<<"\nEnter burst time of the process: \t";
        cin>>burst_time;
        map[arr_time]=burst_time;
    }
    int passed_time=0, count=0;
    for(auto it:process){//iteration through map
        cout<<"Arrival Time: "<<it.first<<"\t Burst Time: "<<it.second<<endl;
    }
    unordered_map<int, int> exit_time_process;
    int exit_time=0;
    for(auto it:process){//computation
        count++;//keeping the count of processes executed/executing
        if(count==1){
            passed_time=passed_time + it.first;
        }
        else{
            if(passed_time==arr_time || passed_time>arr_time){
                passed_time=passed_time+burst_time;
            }
            else{
                passed_time=passed_time + 0.5; //given that smallest unit of time to consider here is 0.5ms
            }
        }
        exit_time=passed_time;
        exit_time_process[burst_time]=exit_time;
    }
    for(auto it:exit_time_process){//iteration through map
        cout<<"Burst Time: "<<it.first<<"\t Exit Time: "<<it.second<<endl;
    }
    //waiting time ke liye alag map bna lo(final)

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
//     int time_passed=0;
//     int termination_time[n], starting_time[n];
//     float avg_wt=0, tot_wt=0, waiting_time[n];
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
//     cout<<"The waiting time of each process is as follows: "<< endl;
//     for(int j=0; j<n; j++){
//         cout<<"Process "<<j+1<<" : "<<waiting_time[j]<<endl;
//     }
//     cout<<endl;
//     cout<<"The avg waiting time is: "<< avg_wt<< endl;

//     return 0;
// };