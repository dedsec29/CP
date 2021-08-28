#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int x,n; cin>>x>>n;
    multiset<int> s;
    s.insert(x);
    set<int> lights;
    lights.insert(0);
    lights.insert(x);
    for (int i = 1; i <= n; i++) {
        int r; cin>>r;
        auto it = lights.upper_bound(r);
        int ub = *it;
        it--;
        int lb = *it;
        s.erase(s.find(ub-lb));
        s.insert(r-lb);
        s.insert(ub-r);
        lights.insert(r);
        cout << *s.rbegin() << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}