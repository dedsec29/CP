#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

int const inf = 1e9+1;

struct Data {
    int x, cnt;

    Data() {}

    Data(int x_) {
        x = x_;
        cnt = 1;
    } 

    Data(int x_,int cnt_) {
        x = x_;
        cnt = cnt_;
    }
};

// Be carefull. Return type of functions in templated classes
// do not give error if returning wrong datatype
template <typename T>
class SegmentTree { // 0 indexed queries
public:
    
    vector<T> t;
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
            t[v] = Data(a[l]);
        else {
            int mid = (l+r)>>1;
            build(a, v<<1, l, mid);
            build(a, (v<<1)+1, mid+1, r);
            t[v] = combine(t[v<<1], t[(v<<1)+1]);
        }
    }

    T combine(T A,T B) {
        if (A.x == B.x)
            return Data(A.x, A.cnt + B.cnt);
        if (A.x < B.x)
            return A;
        return B;
    }

    T query(int l,int r) {
        return query(1, 0, n-1, l, r);
    }

    // tl and tr are segment tree boundaries
    T query(int v,int tl,int tr,int l,int r) {
        // no overlap
        if (tr < l || r < tl)
            return Data(inf);           // NEUTRAL ELEMENT
        
        // completely lies in  (collect all partial overlaps)
        if (l <= tl && tr <= r)
            return t[v];
        int mid = (tl+tr)>>1;
        T left = query(v<<1, tl, mid, l, r);
        T right = query((v<<1)+1, mid+1, tr, l, r);
        return combine(left, right);
    }

    void update(int i,int val) {
        update(1, 0, n-1, i, val);
    }

    void update(int v,int tl,int tr,int idx,int val) {
        if (tl == tr) {
            t[v] = Data(val);
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
    SegmentTree<Data> X;
    X.build(arr);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int i,v; cin >> i >> v;
            X.update(i,v);
        }
        else {
            int l,r; cin >> l >> r;
            r--;
            auto ans = X.query(l, r);
            cout << ans.x << " " << ans.cnt << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}