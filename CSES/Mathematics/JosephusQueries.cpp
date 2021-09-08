#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//Let (n,k) represent state of the game
//then, after going around killing once, game becomes
//(ceil(n/2), k - floor(n/2))   (clearly recursive)
//we just need correct mapping of child games to parent games
//If n even, 
// 1 2 3 4 5 6 =>  1   3   5 
//   x   x   x    (1) (2) (3)
//so mapping is 2*ans - 1

//if n is odd,
// 1 2 3 4 5 6 7 =>  1   3   5   7 
//   x   x   x      (2) (3) (4) (1)
//for correct mapping, do -1 with modulo ceil(n) (1 based indexing modulo)
//                  (1) (2) (3) (4)
//now do 2*ans - 1 

ll func(ll n,ll k) {
    if (n == 1)
        return 1;
    if (k - n/2 <= 0)
        return 2ll*k;
    if (n&1)
        return 2ll*((func(n/2 + (n&1), k - n/2) + (n/2 + (n&1)) - 2ll)%(n/2 + (n&1)) + 1ll) - 1ll;
    return 2ll*func(n/2 + (n&1), k - n/2) - 1ll;
}

void solve() {
    ll n,k; cin>>n>>k;
    cout << func(n,k) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}