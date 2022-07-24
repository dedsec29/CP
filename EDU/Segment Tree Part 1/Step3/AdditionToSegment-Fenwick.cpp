#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

// (Point query + Range updates)
class Fenwick { // 1 based indexing
public:
    int n;
    vector<int> ft;

    Fenwick(int n_) {
        n = n_;
        ft.resize(n+1);
    }

    int qry(int i) {
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

    int query(int i) {
        return qry(i);
    }

    void update(int l,int r,int x) {
        update(l, x);
        if (r < n) update(r+1, -x);
    }
};

void solve() {
    int n,q; cin >> n >> q;
    Fenwick X(n);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l,r,v; cin >> l >> r >> v; l++;
            X.update(l,r,v);
        }
        else {
            int idx; cin >> idx; idx++;
            cout << X.query(idx) << "\n";
        }
    }    
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}