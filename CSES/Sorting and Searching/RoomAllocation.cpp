#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//MEX: https://www.youtube.com/watch?v=JDuVLyKn7Yw
 
struct event {
    int l,r,idx,x;  //x is type-> associated coordinate 
    char type;
    int id;
};
 
bool comp(event& a,event& b) {
    if (a.x != b.x)
        return a.x < b.x;
    if (a.type != b.type)
        return a.type < b.type;
    if (a.type == 'i')
        return a.r > b.r;
    return a.l < b.l;
}
 
void solve() {
    int n; cin>>n;
    vector<event> arr(2*n);
    vector<int> ans(n);
    for (int i=0;i<n;i++) {
        int l,r; cin>>l>>r;
        event e;
        e.l = l, e.r = r, e.idx = i, e.x = l, e.type = 'i';
        arr[i] = e;
        e.x = r, e.type = 'o';
        arr[i+n] = e;
    }
    sort(arr.begin(), arr.end(), comp);
    set<int> A, B;
    for (int i=1;i<=n+1;i++) B.insert(i);
    vector<int> assigned_id(n+1);
 
    for (auto e: arr) {
        if (e.type == 'i') {
            ans[e.idx] = *B.begin();
            e.id = ans[e.idx];
            assigned_id[e.idx] = e.id;
            B.erase(e.id);
            A.insert(e.id);
        }
        else {
            A.erase(assigned_id[e.idx]);
            B.insert(assigned_id[e.idx]);
        }
    }
    cout << *max_element(ans.begin(), ans.end()) << "\n";
    for (int i: ans) cout << i << " ";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}