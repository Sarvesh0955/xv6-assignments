#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    map<string,int> ind;
    vector<string> q(n);
    cout<<"Processes: ";
    for(int i=0;i<n;i++){
        cin>>q[i];
        ind[q[i]] = i;
    }
    
    vector<int> arrival(n);
    cout<<"Arrival time: ";
    for(int i=0;i<n;i++){
        cin>>arrival[i];
    }
    

    vector<int> burst(n);
    vector<int> ori_burst(n);
    int tot_time = 0;
    cout<<"Burst time: ";
    for(int i=0;i<n;i++){
        cin>>burst[i];
        ori_burst[i] = burst[i];
        tot_time += burst[i];
    }

    int time_qant;
    cout<<"Time Quantum: ";
    cin>>time_qant;

    cout<<endl;
    queue<string> pq;
    map<int,vector<string>> m;
    for(int i=0;i<n;i++){
        m[arrival[i]].push_back(q[i]);
    }

    vector<string> gant;
    int total_wait = 0;
    int total_turn = 0;
    vector<int> wait(n);
    vector<int> comp(n);
    vector<int> turn(n);
    for(int i=0;i<=tot_time;i++){
        while(!m[i].empty()){
            pq.push(m[i].back());
            m[i].pop_back();
        }

        if(pq.empty()) continue;

        string t = pq.front();
        pq.pop();
        int j = ind[t];
        if(burst[j]-time_qant <= 0){
            comp[j] = i+burst[j];
            for(int k=0;k<burst[j];k++){
                i++;
                while(!m[i].empty()){
                    pq.push(m[i].back());
                    m[i].pop_back();
                }
            }
            turn[j] = comp[j] - arrival[j];
            wait[j] = turn[j] - ori_burst[j];
            total_wait += wait[j];
            total_turn += turn[j];
            burst[j] = 0;
        }
        else{
            for(int k=0;k<time_qant;k++){
                i++;
                while(!m[i].empty()){
                    pq.push(m[i].back());
                    m[i].pop_back();
                }
            }
            pq.push(t);
            burst[j] -= time_qant;
        }
        gant.push_back(t);
        i--;
    }
    
    double avg_wait = total_wait*1.0 / n;
    double avg_turn = total_turn*1.0 / n;


    cout<<"Gantt Chart: |";
    for(int i=0;i<(int)gant.size();i++){
        cout<<gant[i]<<"|";
    }
    cout<<endl;
    
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
