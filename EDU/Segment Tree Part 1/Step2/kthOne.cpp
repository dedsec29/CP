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

    int kthOne(int k) {
        // If L R were given, could use query at each step for nlognlogn
        return kthOne(1, 0, n-1, k);
    }

    int query(int l,int r) {
        return query(1, 0, n-1, l, r);
    }

    int kthOne(int v,int tl,int tr,int k) {
        if (k > t[v])
            return -1;   // kth Does not exist
        if (tl == tr)
            return tl;
        int mid = (tl+tr)>>1;

        if (k <= t[v<<1])
            return kthOne(v<<1, tl, mid, k);
        else
            return kthOne((v<<1)+1, mid+1, tr, k-t[v<<1]);
    }

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
    int n, q; cin >> n >> q;
    vector<int> arr(n);
    for (int& i: arr) cin >> i;
    SegmentTree X;
    X.build(arr);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int i; cin >> i;
            X.update(i, 1 ^ X.query(i,i));
        }
        else {
            int k; cin >> k; k++;
            cout << X.kthOne(k) << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}