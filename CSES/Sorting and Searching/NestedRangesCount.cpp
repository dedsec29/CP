#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

//Very nice explanation: https://youtu.be/ORdmSir
gp_hash_table<int,int, custom_hash> compress;

struct interval {
    int l,r,idx;
};

bool comp(interval& a,interval& b) {
    return (a.l < b.l) || (a.l == b.l && a.r > b.r);
}

int qry(int i, vector<int>& ft) {
    int sum=0;
    while (i>0) {
        sum+=ft[i];
        i-=i&-i;
    }
    return sum;
}

void update(int i, int x, vector<int>& ft, int n) {
    while (i<=n) {
        ft[i]+=x;
        i+=i&-i;
    }
}

vector<int> solve_part_1(vector<interval>& arr,int n) {
    vector<int> ans(n);
    int sz = compress.size();
    vector<int> ft(sz+1);
    reverse(arr.begin(), arr.end());
    for (auto i: arr) {
        ans[i.idx] = qry(compress[i.r], ft);  //num of elements smaller [1, r]
        update(compress[i.r], 1, ft, sz);
    }
    return ans;
}

vector<int> solve_part_2(vector<interval>& arr,int n) {
    vector<int> ans(n);
    int sz = compress.size();
    vector<int> ft(sz+1);
    for (auto i: arr) {
        ans[i.idx] = qry(sz, ft)-qry(compress[i.r]-1, ft);
        update(compress[i.r], 1, ft, sz);
    }
    return ans;
}

void solve() {
    int n; cin>>n;
    vector<interval> arr(n);
    set<int> sparse;
    for (int i=0;i<n;i++) {
        cin>>arr[i].l>>arr[i].r;
        arr[i].idx = i;
        sparse.insert(arr[i].l);
        sparse.insert(arr[i].r);
    }
    for (int i: sparse)
        compress.insert({i, compress.size()+1});
    sort(arr.begin(), arr.end(), comp);
    vector<int> ans2 = solve_part_2(arr, n);
    vector<int> ans1 = solve_part_1(arr, n);
    for (int i: ans1) cout << i << " ";
    cout << "\n";
    for (int i: ans2) cout << i << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}