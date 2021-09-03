#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
//#pragma GCC optimize "trapv"
#define ll long long

typedef tree<
pair<int,int>,
null_type,
less<pair<int,int>>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

void solve() {
    int n,k; cin>>n>>k;
    vector<int> arr(n);
    for (int& i: arr) cin >> i;
    ordered_set s;
    for (int i=0;i<k-1;i++)
        s.insert({arr[i], i});
    for (int i=k-1;i<n;i++) {
        s.insert({arr[i],i});
        cout << s.find_by_order((k+1)/2 - 1)->first << " ";
        s.erase({arr[i-k+1], i-k+1});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}