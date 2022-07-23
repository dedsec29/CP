#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

// (Range query + Point updates)
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
        return query(r) - query(l-1);
    }
};

void solve() {
    int n; cin >> n;
    vector<int> arr(n+1);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    // Suffix sum, followed by update
    Fenwick X(n);
    for (int i = 1; i <= n; i++) {
        cout << X.query(arr[i], n) << " ";
        X.update(arr[i], 1);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}