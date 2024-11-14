#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    vector<string> q(n);
    cout<<"Processes: ";
    for(int i=0;i<n;i++){
        cin>>q[i];
    }
    
    vector<int> arrival(n);
    cout<<"Arrival time: ";
    for(int i=0;i<n;i++){
        cin>>arrival[i];
    }
    
    vector<int> burst(n);
    cout<<"Burst time: ";
    for(int i=0;i<n;i++){
        cin>>burst[i];
    }
    
    cout<<endl;
    
    cout<<"Gantt Chart: |";
    for(int i=0;i<n;i++){
        cout<<q[i]<<"|";
    }
    cout<<endl;
    
    int t=arrival[0];
    int total_wait = 0;
    int total_turn = 0;
    vector<int> wait(n);
    vector<int> turn(n);
    for(int i=0;i<n;i++){
        wait[i] = max(t-arrival[i],0);
        t += burst[i];
        total_wait += wait[i];
        turn[i] = (t-arrival[i]);
        total_turn += turn[i];
    }
    
    double avg_wait = total_wait*1.0 / n;
    double avg_turn = total_turn*1.0 / n;
    
    cout<<"Waiting Time: ";
    for(int i=0;i<n;i++){
        cout<<q[i]<<"="<<wait[i]<<",";
    }
    cout<<endl;
    
    cout<<"Turnaround Time: ";
    for(int i=0;i<n;i++){
        cout<<q[i]<<"="<<turn[i]<<",";
    }
    cout<<endl;
    
    cout<<"Average Waiting Time: "<<avg_wait<<endl;
    cout<<"Average Turnaround Time:: "<<avg_turn<<endl;
    return 0;
}
