#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
//#pragma GCC optimize "trapv"
#define ll long long

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

void solve() {
    ordered_set s;
    int n,k; cin>>n>>k;
    for (int i=1;i<=n;i++)
        s.insert(i);
    auto it = s.find_by_order(k%n);
    while (!s.empty()) {
        int e = *it;
        cout << e << " " ;
        int num = s.order_of_key(e);
        s.erase(e);
        if (s.empty())
            break;
        it = s.find_by_order((num+k)%s.size());
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}