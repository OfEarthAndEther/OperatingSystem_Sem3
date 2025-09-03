#include <iostream>
using namespace std;

int main(){
    int n;
    cout<<"Enter the number of Processes: ";
    cin>>n;
    int arrival[n];
    cout<<"Enter the arrival time for each process respectively.(in ms)";
    for(int i=0; i<n; i++){
        cin>>arrival[i];
    }// abhi ke liye assuming ki 1st/ ya koi bhi ek process 0ms par aaya (nahi toh sabse choti arrival time ki value ko saari values se minus karke fir calc karte below algo se and final ans report karne par jaha jaha add karna hota kar dete.)
    int burst[n];
    cout<<"Enter the burst time for each process respectively.(in ms)";
    for(int i=0; i<n; i++){
        cin>>burst[i];
    }
// yaha tak hamare pass abhi saari values jo question mai given hongi wo aayi hai.
    int time_passed=0;
    int termination_time[n], starting_time[n];
    float avg_wt=0, tot_wt=0, waiting_time[n];
    for(int j=0; j<n; j++){
        if (time_passed < arrival[j]) {
            time_passed = arrival[j];  // CPU waits till process arrives
        }
        //sort(arrival time values) again assuming ki sorted order mai hi hai given
        starting_time[j]=time_passed;
        time_passed+=burst[j];
        termination_time[j]=time_passed;
        waiting_time[j] = starting_time[j] - arrival[j];
    }
    for(int j=0; j<n; j++){
        tot_wt+=waiting_time[j];
    }
    avg_wt=tot_wt/n;
    cout<<"The waiting time of each process is as follows: "<< endl;
    for(int j=0; j<n; j++){
        cout<<"Process "<<j+1<<" : "<<waiting_time[j]<<endl;
    }
    cout<<endl;
    cout<<"The avg waiting time is: "<< avg_wt<< endl;

    return 0;
};