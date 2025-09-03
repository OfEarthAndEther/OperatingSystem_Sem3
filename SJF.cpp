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
    int time_passed=0, smol=burst[0];
    int copy[n], termination_time[n], starting_time[n];
    float avg_wt=0, tot_wt=0, waiting_time[n];
    //burst array copy kiya
    for(int i=0; i<n; i++){
        copy[i]=burst[i];//same mai changes isliye nahikar rahe taaki changes dekh paye positions ka from original given array
    }
    //bubble sort implement kiya
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            if(copy[j]>copy[j+1]){
                int temp=copy[j];
                copy[j]=copy[j+1];
                copy[j+1]=temp;
            }
        }
    }
    //copied array se original array mai change of place dekh kar index ki array bankar save point ki tarah rakho and calculate aage ka sab kuch as it is. last mai bas ans show karte waqt save points ko refer karo.
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
    cout<<"The waiting time of each process is as follows: ";
    for(int j=0; j<n; j++){
        cout<<waiting_time[j]<<endl;
    }
    cout<<endl;
    cout<<"The avg waiting time is: "<< avg_wt<< endl;


    return 0;
}