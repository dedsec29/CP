#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin>>n>>m;
    multiset<int> s;
    for (int i=0;i<n;i++) {
        int r; cin>>r;
        s.insert(r);
    }
    while (m--) {
        int p; cin>>p;
        auto it = s.upper_bound(p);
        if (it==s.begin()) 
            cout<<"-1\n";
        else {
            --it;
            cout<<(*it)<<"\n";
            s.erase(it);
        }
    }
    return 0;
}