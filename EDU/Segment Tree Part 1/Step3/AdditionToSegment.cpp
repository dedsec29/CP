#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

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
        return A + B;
    }

    int query(int l,int r) {
        return query(1, 0, n-1, l, r);
    }

    // tl and tr are segment tree boundaries
    int query(int v,int tl,int tr,int l,int r) {
        // no overlap
        if (tr < l || r < tl)
            return 0;           // NEUTRAL ELEMENT
        
        // completely lies in  (collect all partial overlaps)
        if (l <= tl && tr <= r)
            return t[v];
        int mid = (tl+tr)>>1;
        int left = query(v<<1, tl, mid, l, r);
        int right = query((v<<1)+1, mid+1, tr, l, r);
        return combine(left, right);
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
    // Just like Fenwick Range update + Point Query
    int n,q; cin >> n >> q;
    SegmentTree X(n+1);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l,r,v; cin >> l >> r >> v; r--;
            int old_l = X.query(l, l);
            int old_r = X.query(r+1, r+1);
            X.update(l, v + old_l);
            X.update(r+1, old_r - v);
        }
        else {
            int idx; cin >> idx;
            cout << X.query(0, idx) << "\n";
        }
    }    
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}