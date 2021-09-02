#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    vector<int> arr(n), ans(n,-1);
    for (int& i: arr) cin>>i;
    stack<int> s;
    for (int i=n-1;i>=0;i--) {
        while (!s.empty() && arr[i] < arr[s.top()]) {
            ans[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    for (int i: ans) cout << i+1 << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}