#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")

// https://codeforces.com/contest/940/problem/F

struct range_query {
    int L,R, Lbno, Rbno, time, idx;

    range_query() {}

    range_query(int L_,int R_,int Lbno_,int Rbno_,int time_,int idx_) {
        L = L_, R = R_, Lbno = Lbno_, Rbno = Rbno_;
        time = time_, idx = idx_;
    }
};

struct update_query {
    int idx, old_val, new_val;

    update_query() {}

    update_query(int idx_,int old_val_,int new_val_) {
        idx = idx_, old_val = old_val_, new_val = new_val_;
    }
};

int const siz = 2e5 + 10;
int arr[siz], freq[siz], ffreq[siz], block_size, ans[siz];
range_query Q[siz];
update_query UPD[siz];

void add(int x) {
    ffreq[freq[x]]--;
    freq[x]++;
    ffreq[freq[x]]++;
}

void remove(int x) {
    ffreq[freq[x]]--;
    freq[x]--;
    ffreq[freq[x]]++;
}

void to_future(int timer,int L,int R) {
    if (L <= UPD[timer].idx && UPD[timer].idx <= R) {
        remove(UPD[timer].old_val);
        add(UPD[timer].new_val);
    }
    arr[UPD[timer].idx] = UPD[timer].new_val;
}

void to_past(int timer,int L,int R) {
    if (L <= UPD[timer].idx && UPD[timer].idx <= R) {
        remove(UPD[timer].new_val);
        add(UPD[timer].old_val);
    }
    arr[UPD[timer].idx] = UPD[timer].old_val;
}

bool compare(range_query& A,range_query& B) {
    if (A.Lbno != B.Lbno)
        return A.Lbno < B.Lbno;
    if (A.Rbno != B.Rbno)
        return A.Rbno < B.Rbno;
    return A.time < B.time;
}

void solve() {
    set<int> sparse;
    map<int,int> compress;

    int n,q; cin >> n >> q;
    block_size = pow(n, 0.667);

    vector<int> upd_arr(n+1);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sparse.insert(arr[i]);
    }

    vector<tuple<int,int,int>> input_queries(q+1);
    for (int i = 1; i <= q; i++) {
        int a,b,c; cin >> a >> b >> c;
        if (a == 2) {
            --b;
            sparse.insert(c);
        }
        else {
            --b; --c;
        }
        input_queries[i] = {a,b,c};
    }

    for (int i: sparse)
        compress.insert({i, compress.size()+1});
    for (int i = 0; i < n; i++) 
        upd_arr[i] = arr[i] = compress[arr[i]];

    for (int i = 1; i <= q; i++) {
        if (get<0>(input_queries[i]) == 2)
            get<2>(input_queries[i]) = compress[get<2>(input_queries[i])];
    }

    int cntq = 0, cntu = 0; // timer, from t = 1
    for (int i = 1; i <= q; i++) {
        int type = get<0>(input_queries[i]);
        if (type == 1) {
            int l = get<1>(input_queries[i]);
            int r = get<2>(input_queries[i]);
            ++cntq;
            Q[cntq] = range_query(l, r, l/block_size, r/block_size, cntu, cntq);
        }
        else {
            int p = get<1>(input_queries[i]);
            int x = get<2>(input_queries[i]);
            UPD[++cntu] = update_query(p, upd_arr[p], x);
            upd_arr[p] = x;
        }
    }

    sort(Q+1, Q+cntq+1, compare);

    int L = 0, R = -1, timer = 0;
    for (int i = 1; i <= cntq; i++) {
        while (R < Q[i].R) 
            add(arr[++R]);
        while (L > Q[i].L) 
            add(arr[--L]);
        while (R > Q[i].R)
            remove(arr[R--]);
        while (L < Q[i].L)
            remove(arr[L++]);
        while (timer < Q[i].time)
            to_future(++timer, L, R);
        while (timer > Q[i].time)
            to_past(timer--, L, R);
        
        // finding mex takes O(sqrt(n)) cause of O(sqrt(n)) distinct freq
        int mex = 1;
        while (ffreq[mex])
            mex++;
        ans[Q[i].idx] = mex;
    }
    for (int i = 1; i <= cntq; i++)
        cout << ans[i] << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}