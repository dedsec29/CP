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

void work(int n,vector<int>& arr,vector<int>& ans) {
    SegmentTree X(2*n);
    vector<int> first_idx(n+1, -1);
    for (int i = 2*n-1; i >= 0; i--) 
        first_idx[arr[i]] = i;
    for (int i = 0; i < 2*n; i++) {
        if (first_idx[arr[i]] == i) 
            X.update(first_idx[arr[i]], 1);
        else {
            X.update(first_idx[arr[i]], 0);
            ans[arr[i]] += X.query(first_idx[arr[i]], i);
        }
    }
}

void solve() {
    int n; cin >> n;
    vector<int> arr(2*n);
    for (int& i: arr) cin >> i;
    vector<int> ans(n+1);
    //         x  y        x    y
    // Finding x  y(start) x  
    // (Find   y  x(end)   y  by reversing array)
    work(n, arr, ans);
    reverse(arr.begin(), arr.end());
    work(n, arr, ans);
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}