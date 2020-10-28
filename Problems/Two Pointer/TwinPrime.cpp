#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const n = 2e7;
int const siz = 1e5;
bitset<n> is_prime;
pair<int,int> answer[siz+1];

void precomputation() {
    is_prime.set();
    is_prime[0] = is_prime[1] = 1;
    for (ll i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i)
                is_prime[j] = 0;
        }
    }
    vector<int> v;
    for (int i=2;i<=n;i++) if (is_prime[i]) v.push_back(i);
    int l=0,r=1, k=0;
    while (r<=n) {
        if (l==r) {
            r++;
            continue;
        }
        if (v[r]-v[l] < 2) r++;
        else if (v[r]-v[l] > 2) l++;
        else {
            k++; 
            answer[k] = {v[l],v[r]};
            if (k==siz) break;
            r++;
        }
    }
}

void solve(ll a) {
    cout<<"("<<answer[a].first<<", "<<answer[a].second<<")\n";
}

int main() {
    precomputation();
    ll a;
    string line;
    while (scanf("%lld", &a)==1) 
        solve(a);
    return 0;
}