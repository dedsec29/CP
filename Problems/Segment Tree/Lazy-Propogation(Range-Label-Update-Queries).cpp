#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

// https://www.topcoder.com/thrive/articles/range-operations-lazy-propagation
// https://codeforces.com/contest/558/problem/E

int const al = 26;
int const inf = 0;

class SegmentTree { // 0 indexed queries
public:
    // put in lazy what you want to spread
    // Then in node, we spread it times the range size
    vector<int> t, lazy;
    int n;
 
    SegmentTree() {}
 
    // Creates an empty segment tree
    SegmentTree(int n_) {
        n = n_;
        t.resize(4*n);
        lazy.assign(4*n, -1);
    }
 
    // Create fron arr
    void build(vector<int>& a) {
        n = a.size();
        t.resize(4*n);
        lazy.assign(4*n, -1);
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
        return A+B;
    }
 
    int query(int l,int r) {
        return query(1, 0, n-1, l, r);
    }
 
    // tl and tr are segment tree boundaries
    int query(int v,int tl,int tr,int l,int r) {
        if (lazy[v] != -1) {
            t[v] = (tr-tl+1) * lazy[v];
            if (tl != tr) {
                lazy[v<<1] = lazy[v];
                lazy[(v<<1)+1] = lazy[v];
            }
            lazy[v] = -1;
        }
 
        // no overlap
        if (tr < l || r < tl)
            return inf;           // NEUTRAL ELEMENT
        
        // completely lies in  (collect all partial overlaps)
        if (l <= tl && tr <= r)
            return t[v];
        int mid = (tl+tr)>>1;
        int left = query(v<<1, tl, mid, l, r);
        int right = query((v<<1)+1, mid+1, tr, l, r);
        return combine(left, right);
    }
 
    void update(int l,int r,int val) {
        update(1, 0, n-1, l, r, val);
    }
 
    // range label query
    void update(int v,int tl,int tr,int l,int r,int val) {
        if (lazy[v] != -1) {
 
            t[v] = (tr-tl+1) * lazy[v];
 
            if (tl != tr) { // not a leaf, so we ma
                lazy[v<<1] = lazy[v];
                lazy[(v<<1)+1] = lazy[v];
            }
            lazy[v] = -1;       // no longer lazy
        }
 
        if (tr < l || r < tl)
            return;
        // complete overlap
        if (l <= tl && tr <= r) {
            t[v] = (tr-tl+1) * val;
            if (tl != tr) { // not a leaf, so we mark children lazy
                lazy[v<<1] = val;
                lazy[(v<<1)+1] = val;
            }
            return;
        }
        int mid = (tl+tr)>>1;
        update(v<<1, tl, mid, l, r, val);
        update((v<<1)+1, mid+1, tr, l, r, val);
        t[v] = combine(t[v<<1], t[(v<<1)+1]);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<SegmentTree> arr(al);
    for (int i = 0; i < al; i++)
        arr[i] = SegmentTree(n);
    for (int i = 0; i < n; i++) 
        arr[s[i]-'a'].update(i,i,1);
    while (q--) {
        int l,r,k; cin >> l >> r >> k; --l, --r;
        if (k == 1) {
            int ptr = l;
            for (int c = 0; c < al; c++) {
                int cnt = arr[c].query(l, r);
                if (cnt == 0)
                    continue;
                arr[c].update(ptr, ptr + cnt - 1, 1);
                if (ptr-1 >= l)
                    arr[c].update(l, ptr-1, 0);
                if (ptr+cnt <= r)
                    arr[c].update(ptr+cnt, r, 0);
                ptr += cnt;
            }
        }
        else {
            int ptr = r;
            for (int c = 0; c < al; c++) {
                int cnt = arr[c].query(l, r);
                if (cnt == 0)
                    continue;
                arr[c].update(ptr - cnt + 1, ptr, 1);
                if (ptr-cnt >= l)
                    arr[c].update(l, ptr-cnt, 0);
                if (ptr+1 <= r)
                    arr[c].update(ptr+1, r, 0);
                ptr -= cnt;
            }
        }
    }
    string ans = "";
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < al; c++) {
            if (arr[c].query(i,i) == 1) {
                ans += ('a' + c);
                break;
            }
        }
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}