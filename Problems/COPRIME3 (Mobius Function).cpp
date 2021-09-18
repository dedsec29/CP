#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//https://codeforces.com/blog/entry/53925
//https://artofproblemsolving.com/community/c90633h1291397_number_theory_in_competitive_programming_tutorial

int const siz = 1e6;
bitset<siz+1> is_prime;
int mu[siz+1], freq[siz+1];

void mobius() {
    is_prime.set();
    vector<int> primes;
    mu[1] = 1;
    for (int i = 2; i <= siz; ++i) {
        if (is_prime[i]) {
            mu[i] = -1;
            primes.push_back(i);
        }
        for (int j = 0; j < (int) primes.size() && i * primes[j] <= siz; ++j) {
            is_prime[i * primes[j]] = 0;
            if (i % primes[j] == 0) {
                mu[i * primes[j]] = 0;
                break;
            } 
            else 
                mu[i * primes[j]] = -mu[i];
        }
    }
}

ll choose3(ll n) {
    return (((n*(n-1))/2)*(n-2))/3;
}

void solve() {
    int n; cin>>n;
    int mx = 0;
    for (int i=1;i<=n;i++) {
        int r; cin>>r;
        freq[r]++;
        mx = max(mx, r);
    }
    vector<int> divides_cnt(mx+1);  //i divides how many elements
    for (int i = 1; i <= mx; i++) {
        for (int j = i; j <= mx; j += i)
            divides_cnt[i] += freq[j];
    }
    ll ans = 0;
    for (int i = 1; i <= mx; i++) 
        ans += ((ll) mu[i]) * choose3(divides_cnt[i]);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    mobius();
    solve();
    return 0;
}