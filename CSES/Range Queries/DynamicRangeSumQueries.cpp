#include <bits/stdc++.h>
using namespace std;
#define int long long

class SegmentTree {
    const static int neutral_element = 0;
    vector<int> t;
    int n = 0;

    void build(int v,int l,int r,const vector<int>& nums) {
        if (l == r) {
            t[v] = nums[l];
            return;
        }
        int mid = (l+r)>>1;
        build(v*2, l, mid, nums);
        build(v*2+1, mid+1, r, nums);
        t[v] = combine(t[v*2], t[v*2 + 1]);
    }

    int query(int v,int tl,int tr,int l,int r) {
        if (r < tl || tr < l)   // disjoint
            return neutral_element;
        if (l <= tl && tr <= r)     // add contribution if t[v] completely inside
            return t[v];
        int mid = (tl + tr) >> 1;
        return combine( query(v*2, tl, mid, l, r), query(v*2+1, mid+1, tr, l, r) );
    }

    void update(int v,int tl,int tr,int i,int x) {
        if (tl == tr) {
            t[v] = x;
            return;
        }
        int mid = (tl + tr) >> 1;
        if (i <= mid)
            update(v*2, tl, mid, i, x);
        else
            update(v*2+1, mid+1, tr, i, x);
        t[v] = combine(t[v*2], t[v*2+1]);
    }

    int combine(int a,int b) {
        return a + b;
    }

public:

    void build(const vector<int>& nums) {
        n = nums.size();
        t.resize(4*n);
        build(1, 0, n-1, nums);
    }

    int query(int l,int r) {
        return query(1, 0, n-1, l, r);
    }

    void update(int i,int x) {
        update(1, 0, n-1, i, x);
    }
};

void solve() {
    int n,q; cin >> n >> q;
    vector<int> arr(n);
    for (int& i: arr) cin >> i;
    SegmentTree X;
    X.build(arr);
    while (q--) {
        int a,b,c; cin >> a >> b >> c;
        if (a == 1) {
            --b;
            X.update(b, c);
        }
        else {
            b--; c--;
            cout << X.query(b, c) << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
