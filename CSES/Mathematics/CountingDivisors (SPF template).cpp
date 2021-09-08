#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;
int const siz = 1e6;

bitset<siz+1> bits;
int spf[siz+1];

void precomputation() {
    for(int i = 2; i <= siz; i += 2)
        spf[i] = 2 ;
    int sq = sqrt(siz);
    for (int i = 3; i <= siz; i += 2) {
        if (!bits[i]) {
            spf[i] = i;
            if (i <= sq) for (int j = i*i; j <= siz; j += 2*i) {
                if (!bits[j]) {
                    spf[j] = i;
                    bits[j] = 1;
                }
            }
        }
    }
}

ll perform(int N) {
    ll ans = 1;
    int z=N;
    int curr = spf[z];
    int cnt = 1;
    while (z > 1) {
        z /= spf[z];
        if (curr == spf[z]) {
            cnt++; 
            continue; 
        } 
        //mp.insert({curr,cnt});
        ans = ans * ((ll) cnt + 1) % mod;
        curr = spf[z]; 
        cnt = 1; 
    }
    return ans;
}

void solve() {
    int x; cin>>x;
    cout << perform(x) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precomputation();
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}