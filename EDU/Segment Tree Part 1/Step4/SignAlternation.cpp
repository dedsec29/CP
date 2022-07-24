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
    int n; cin >> n;
    vector<int> arr(n), arr0(n), arr1(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (i&1) arr1[i] = arr[i];
        else arr0[i] = arr[i];
    }
    SegmentTree X0, X1;
    X0.build(arr0);
    X1.build(arr1);
    int q; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 0) {
            int i,j; cin >> i >> j; --i;
            if (i&1) X1.update(i, j);
            else X0.update(i, j);
        }
        else {
            int l,r; cin >> l >> r; --l, --r;
            int ans = X0.query(l,r) - X1.query(l,r);
            if (l&1) ans = -ans;
            cout << ans << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}