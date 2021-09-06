#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n,k; cin>>n>>k;
    int bad = 0;
    multiset<int> s;
    vector<pair<int,int>> arr(n);
    for (auto& i: arr) 
        cin >> i.first >> i.second;
    sort(arr.begin(), arr.end(), [](pair<int,int>& a,pair<int,int>& b) {
        return a.second < b.second;
    });
    //greedy: assign latest free
    for (auto i: arr) {
        if (s.empty()) {
            s.insert(i.second);
            continue;
        }
        auto it = s.upper_bound(i.first);
        if (it == s.begin()) {  //.l greater than none .r
            if ((int)s.size() < k)
                s.insert(i.second);
            else
                bad++;
        }
        else {
            --it;
            s.erase(it);
            s.insert(i.second);
        }
    }
    cout << n-bad;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}