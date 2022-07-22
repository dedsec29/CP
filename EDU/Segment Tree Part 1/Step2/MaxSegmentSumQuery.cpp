#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

int const inf = -1e15;

struct Data {
    int sum, pre, suff, ans;

    Data() {}

    Data(int x) {
        sum = pre = suff = ans = x;
    } 

    Data(int sum_,int pre_,int suff_,int ans_) {
        sum = sum_;
        pre = pre_;
        suff = suff_;
        ans = ans_;
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
        int sum = A.sum + B.sum;
        int pre = max(A.pre, A.sum + B.pre);
        int suff = max(B.suff, B.sum + A.suff);
        int ans = max({A.ans, B.ans, A.suff + B.pre});
        return Data(sum, pre, suff, ans);
    }

    T query(int l,int r) {
        return query(1, 0, n-1, l, r);
    }

    // tl and tr are segment tree boundaries
    T query(int v,int tl,int tr,int l,int r) {
        // no overlap
        if (tr < l || r < tl)
            return Data(inf,inf,inf,inf);           // NEUTRAL ELEMENT
        
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
    cout << max(X.query(0, n-1).ans, 0ll) << "\n";
    while (q--) {
        int i,v; cin >> i >> v;
        X.update(i,v);
        cout << max(X.query(0, n-1).ans, 0ll) << "\n";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}