#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    list<int> people;
    for (int i=1;i<=n;i++) people.push_back(i);
    bool kill = false;
    auto it = people.begin();
    while (!people.empty()) {
        if (!kill) {
            kill = true;
            ++it;
            if (it==people.end())
                it = people.begin();
        }
        else {
            cout<<*it<<" ";
            it = people.erase(it);
            if (it==people.end())
                it = people.begin();
            kill = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}