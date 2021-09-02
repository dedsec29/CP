#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma")

void solve() {
    int n,x; cin>>n>>x;
    vector<pair<int,int>> arr(n+1);
    for (int i=1;i<=n;i++) {
        cin>>arr[i].first;
        arr[i].second = i;
    }
    sort(arr.begin()+1, arr.end());
    for (int i=1;i<=n;i++) {
        int target = x - arr[i].first;
        if (target < 0) continue;
        int l = 1, r = n;
        while (l < r) {
            if (arr[l].second != arr[i].second && arr[r].second != arr[i].second && arr[l].first + arr[r].first == target) {
                cout << arr[l].second << " " << arr[r].second << " " << arr[i].second << "\n";
                return;
            }
            else if (arr[l].first + arr[r].first < target)
                l++;
            else
                r--;
        }
    }
    cout << "IMPOSSIBLE";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}