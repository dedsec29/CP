#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//Very nice explanation: https://youtu.be/ORdmSirqrMs

struct interval {
    int l,r,idx;
};

bool comp(interval& a,interval& b) {
    return (a.l < b.l) || (a.l == b.l && a.r > b.r);
}

vector<int> solve_part_1(vector<interval>& arr,int n) {
    int id = n-1;
    vector<int> ans(n);
    for (int i=n-2;i>=0;i--) {
        ans[arr[i].idx] = (arr[i].r >= arr[id].r);
        if (arr[id].r >= arr[i].r)
            id = i;
    }
    return ans;
}

vector<int> solve_part_2(vector<interval>& arr,int n) {
    int id = 0;
    vector<int> ans(n);
    for (int i=1;i<n;i++) {
        ans[arr[i].idx] = (arr[i].r <= arr[id].r);
        if (arr[i].r >= arr[id].r)
            id = i; 
    }
    return ans;
}

void solve() {
    int n; cin>>n;
    vector<interval> arr(n);
    for (int i=0;i<n;i++) {
        cin>>arr[i].l>>arr[i].r;
        arr[i].idx = i;
    }
    sort(arr.begin(), arr.end(), comp);
    vector<int> ans1 = solve_part_1(arr, n);
    vector<int> ans2 = solve_part_2(arr, n);
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