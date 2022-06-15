#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

class SparseTable {
public:
    int n, ub;
    vector<vector<int>> sparse;

    SparseTable(vector<int>& arr) {
        n = arr.size();
        ub = __lg(n);
        sparse = vector<vector<int>>(n, vector<int>(ub + 1));

        for (int i=0;i<n;i++)
            sparse[i][0] = arr[i];
        for (int j=1;j<=ub;j++)
            for (int i=0;i+(1<<j)-1<n;i++)
                sparse[i][j] = __gcd(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
    }

    int query(int l,int r) {
        int interval = r-l+1;
        int jump = __lg(interval);
        return __gcd(sparse[l][jump], sparse[r-(1<<jump)+1][jump]);
    }
};

void solve() {
    int n,q; cin >> n >> q;
    vector<int> A(n), B(n);
    for (int& i: A) cin >> i;
    for (int& i: B) cin >> i;
    vector<int> diffA(n), diffB(n);
    for (int i = 1; i < n; i++) {
        diffA[i] = A[i] - A[i-1];
        diffB[i] = B[i] - B[i-1];
    }
    SparseTable spA(diffA), spB(diffB); 
    
    while (q--) {
        int h1,h2,w1,w2; cin >> h1 >> h2 >> w1 >> w2;
        h1--, h2--, w1--, w2--;
        int x = (w1 == w2) ? 0 : spB.query(w1+1, w2);
        int y = (h1 == h2) ? 0 : spA.query(h1+1, h2);
        int ans = __gcd(A[h1] + B[w1], __gcd(x,y));
        cout << abs(ans) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}