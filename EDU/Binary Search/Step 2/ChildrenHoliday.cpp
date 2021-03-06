#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m,n; cin>>m>>n;
    int z[n], t[n], w[n], counter=0;    //balloons, time, waiting
    int reps[n] = {0};
    int no_ans[n] = {0};
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> timeb, waiting;
    for (int i=0;i<n;i++) {
        int ti,yi,zi; cin>>ti>>zi>>yi;
        timeb.push({ti, i});
        t[i] = ti;
        w[i] = yi;
        z[i] = zi;
    }
    int seconds = 0;
    while (counter<m) {
        seconds++;
        while (!waiting.empty() && waiting.top().first-seconds==0) {
            auto x = waiting.top();
            waiting.pop();
            timeb.push({seconds+t[x.second], x.second});
            reps[x.second] = 0;
        }
        while (!timeb.empty() && timeb.top().first-seconds==0) {
            auto x = timeb.top();
            timeb.pop();
            counter++;
            no_ans[x.second]++;
            reps[x.second]++;
            if (counter==m)
                break;
            if (reps[x.second]==z[x.second]) 
                waiting.push({seconds+w[x.second], x.second});
            else
                timeb.push({seconds+t[x.second], x.second});
        }
    }
    cout<<seconds<<"\n";
    for (int i=0;i<n;i++) cout<<no_ans[i]<<" ";
    return 0;
}