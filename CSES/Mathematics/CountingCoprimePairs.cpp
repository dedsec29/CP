#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e6;
ll freq[siz+1], divides_cnt[siz+1]; //I divide how many
vector<ll> prime_divisors[siz+1];   //siz can't have more than 7 unique pf
bitset<siz+1> is_prime, taken;

ll choose2(ll n) {
    return (n * (n-1))/2;
}

void solve() {
    ll n; cin>>n;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        int r; cin>>r;
        freq[r]++;
        mx = max(mx, r);
    }
    is_prime.set();
    for (int i = 2; i <= mx; i++) {
        for (int j = i; j <= mx; j += i)
            divides_cnt[i] += freq[j];
    }
    int sq = sqrt(mx);
    for (int i = 2; i <= mx; i++) {
        if (is_prime[i]) {
            if (i <= sq) for (int j = i*i; j <= mx; j += i) 
                is_prime[j] = 0;
        }
    }
    for (int i = 2; i <= mx; i++) {
        if (is_prime[i]) {
            for (int j = i; j <= mx; j += i)
                prime_divisors[j].push_back(i);
        }
    }
    ll sub = 0;
    for (int i = 2; i <= mx; i++) {
        int len = prime_divisors[i].size();
        int ub = 1<<len;
        for (int j = 1; j < ub; j++) {
            int sb = 0;
            ll intersection = 1;
            for (int k = 0; k < len; k++) {
                if (j & (1<<k)) {
                    sb++;
                    intersection *= prime_divisors[i][k];
                }
            }
            if (!taken[intersection]) {
                if (sb & 1)
                    sub += choose2(divides_cnt[intersection]);
                else
                    sub -= choose2(divides_cnt[intersection]);   
                taken[intersection] = 1;
            }
        }
    }
    cout << choose2(n) - sub;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}