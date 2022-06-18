#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// up[i][j] = i's 2^j th ancestor
// up[i][j] = up[ up[i][j-1] ][j-1]

class BinaryLifting {
public:
    int n,ub;
    vector<int> parent;
    vector<vector<int>> up;

    BinaryLifting(int n_, vector<int> par) {
        n = n_;
        parent = vector<int>(par);
        ub = __lg(n);

        up = vector<vector<int>>(n+1, vector<int>(ub+1, -1));
        for (int i = 1; i <= n; i++)
            up[i][0] = parent[i];
        for (int j = 1; j <= ub; j++) {
            for (int i = 1; i <= n; i++) {
                if (up[i][j-1] == -1)
                    up[i][j] = -1;
                else
                    up[i][j] = up[ up[i][j-1] ][j-1];
            }
        }
    }

    int kthAncestor(int v,int k) {
        // k as sum of powers of 2 (binary)
        for (int i = 0; k != 0 && i <= ub; i++, k >>= 1) {
            if (k&1) {
                if (up[v][i] == -1)
                    return -1;
                v = up[v][i];
            }
        }
        if (k != 0)
            return -1;
        return v;
    }
};

void solve() {
    int n,q; cin >> n >> q;
    vector<int> parent(n+1, -1);
    for (int i = 2; i <= n; i++) cin >> parent[i];
    BinaryLifting X(n, parent);
    while (q--) {
        int x,k; cin >> x >> k;
        cout << X.kthAncestor(x,k) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}