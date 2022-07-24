#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

int mod = 1;

struct Data {
    int a,b,c,d;

    Data() {}

    Data(int a_,int b_,int c_,int d_) {
        a = a_%mod, b = b_%mod, c = c_%mod, d = d_%mod;
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
    void build(vector<T>& a) {
        n = a.size();
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }

    void build(vector<T>& a,int v,int l,int r) {
        if (l == r)
            t[v] = a[l];
        else {
            int mid = (l+r)>>1;
            build(a, v<<1, l, mid);
            build(a, (v<<1)+1, mid+1, r);
            t[v] = combine(t[v<<1], t[(v<<1)+1]);
        }
    }

    T combine(T k1,T k2) {
        int a = ((k1.a*k2.a)%mod + (k1.b*k2.c)%mod)%mod;
        int b = ((k1.a*k2.b)%mod + (k1.b*k2.d)%mod)%mod;
        int c = ((k1.c*k2.a)%mod + (k1.d*k2.c)%mod)%mod;
        int d = ((k1.c*k2.b)%mod + (k1.d*k2.d)%mod)%mod;
        return Data(a,b,c,d);
    }

    T query(int l,int r) {
        return query(1, 0, n-1, l, r);
    }

    // tl and tr are segment tree boundaries
    T query(int v,int tl,int tr,int l,int r) {
        // no overlap
        if (tr < l || r < tl)
            return Data(1,0,0,1);           // NEUTRAL ELEMENT
        
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
    cin >> mod;
    int n,q; cin >> n >> q;
    vector<Data> arr(n);
    for (int i = 0; i < n; i++) 
        cin >> arr[i].a >> arr[i].b >> arr[i].c >> arr[i].d;
    SegmentTree<Data> X;
    X.build(arr);
    while (q--) {
        int l,r; cin >> l >> r; l--, r--;
        auto ans = X.query(l,r);
        cout << ans.a << " " << ans.b << "\n" << ans.c << " " << ans.d << "\n\n";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}