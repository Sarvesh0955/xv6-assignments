#include <bits/stdc++.h>
using namespace std;

class Compare {
public:
    bool operator()(pair<int,string> &a,pair<int,string> &b){
        if(a.first==b.first)
            return a.second > b.second;
        return a.first>b.first;
    }
};

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
    int tot_time = 0;
    cout<<"Burst time: ";
    for(int i=0;i<n;i++){
        cin>>burst[i];
        tot_time += burst[i];
    }
    cout<<endl;

    priority_queue<pair<int,string>,vector<pair<int,string>>,Compare> pq;
    map<int,vector<pair<int,string>>> m;
    for(int i=0;i<n;i++){
        m[arrival[i]].push_back({burst[i],q[i]});
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
        pair<int,string> t = pq.top();
        pq.pop();
        if(t.first-1>0)
            pq.push({t.first-1,t.second});
        else{
            int j = ind[t.second];
            comp[j] = i+1;
            turn[j] = comp[j] - arrival[j];
            wait[j] = turn[j] - burst[j];
            total_wait += wait[j];
            total_turn += turn[j];
        }
        if(gant.size()==0 || gant.back()!=t.second)
            gant.push_back(t.second);
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
