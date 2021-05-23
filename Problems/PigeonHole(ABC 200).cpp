#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize "trapv"
#define ll long long

vector<int> rem1[200], rem2[200];

void solve() {
    int n; cin>>n;
    int arr[n];
    for (int i=0;i<n;i++) cin>>arr[i];
    int len = min(8,n);
    int ub = 1<<len;
    for (int i=1;i<ub;i++) {
        vector<int> v;
        ll sum = 0;
        for (int j=0;j<len;j++) {
            if (i & (1<<j)) {
                sum = (((ll) arr[j]) + sum)%200;
                v.push_back(j+1);
            }
        }
        if (rem1[sum].empty())
            rem1[sum] = v;
        else if (rem2[sum].empty()) {
            rem2[sum] = v;
            break;
        }
        else {}
    }
    bool exists = false;
    int id = 0;
    for (int i=0;i<200;i++) {
        if (!rem1[i].empty() && !rem2[i].empty()) {
            exists = true;
            id = i;
            break;
        }
    }
    if (!exists) cout<<"No\n";
    else {
        cout<<"Yes\n";
        cout<<rem1[id].size()<<" ";
        for (int i: rem1[id]) cout<<i<<" ";
        cout<<"\n"<<rem2[id].size()<<" ";
        for (int i: rem2[id]) cout<<i<<" ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}