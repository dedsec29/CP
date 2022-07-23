#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

int const inf = -1;

class SegmentTree { // 0 indexed queries
public:
    vector<int> t;
    int n;

    SegmentTree() {}

    // Creates an empty segment tree
    SegmentTree(int n_) {
        n = n_;
        t.resize(4*n);
    }

    // Create fron arr
    void build(vector<int>& a) {
        n = a.size();
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }

    void build(vector<int>& a,int v,int l,int r) {
        if (l == r)
            t[v] = a[l];
        else {
            int mid = (l+r)>>1;
            build(a, v<<1, l, mid);
            build(a, (v<<1)+1, mid+1, r);
            t[v] = combine(t[v<<1], t[(v<<1)+1]);
        }
    }

    int combine(int A,int B) {
        return max(A,B);
    }

    int lowerbound(int x,int l) {
        // If L R were given, could use query at each step for nlognlogn
        return lowerbound(1, 0, n-1, x, l);
    }

    int lowerbound(int v,int tl,int tr,int x,int l) {
        if (x > t[v] || tr < l) 
            return -1;   // No j exists
        if (tl == tr) 
            return tl;
        int mid = (tl+tr)>>1;
        // as left as possible
        if (x <= t[v<<1]) {
            int left = lowerbound(v<<1, tl, mid, x, l);
            if (left != -1)
                return left;
            // above happens only once. So just +logn computations more
            return lowerbound((v<<1)+1, mid+1, tr, x, l);   
            // could have done case work ^ here but base condition handles it
        }
        else
            return lowerbound((v<<1)+1, mid+1, tr, x, l);   
    }

    void update(int i,int val) {
        update(1, 0, n-1, i, val);
    }

    void update(int v,int tl,int tr,int idx,int val) {
        if (tl == tr) {
            t[v] = val;
            return;
        }
        int mid = (tl+tr)>>1;
        if (idx <= mid)
            update(v<<1, tl, mid, idx, val);
        else
            update((v<<1)+1, mid+1, tr, idx, val);
        t[v] = combine(t[v<<1], t[(v<<1)+1]);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    vector<int> arr(n);
    for (int& i: arr) cin >> i;
    SegmentTree X;
    X.build(arr);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int i,v; cin >> i >> v;
            X.update(i, v);
        }
        else {
            int x,l; cin >> x >> l;
            cout << X.lowerbound(x, l) << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}