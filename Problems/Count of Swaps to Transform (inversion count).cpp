// https://codeforces.com/contest/1430/problem/E
#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

class Fenwick { // 1 based indexing
public:
    int n;
    vector<int> ft;

    Fenwick(int n_) {
        n = n_;
        ft.resize(n+1);
    }

    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += ft[i];
            i -= i&-i;
        }
        return sum;
    }

    void update(int i, int x) {
        while (i <= n) {
            ft[i] += x;
            i += i&-i;
        }
    }

    int query(int l,int r) {
        if (l > r)
            return 0;
        return query(r) - query(l-1);
    }
};

int inv_count(vector<int>& arr) {
    int n = arr.size();
    Fenwick X(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += X.query(arr[i]+1, n);
        X.update(arr[i], 1);
    }
    return ans;
}

int swaps_to_goal(string& s,string& goal) {
    int n = s.size();
    vector<queue<int>> indices(26);
    for (int i = 0; i < n; i++)
        indices[goal[i]-'a'].push(i);
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = indices[s[i]-'a'].front() + 1; // inv_count of 1 based index permutation
        indices[s[i]-'a'].pop();
    }
    return inv_count(arr);
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    string goal = s;
    reverse(goal.begin(), goal.end());
    cout << swaps_to_goal(s, goal) << "\n";   
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}