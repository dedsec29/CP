#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

struct query {
    int L,R, bn, index;
};

int const siz = 3e5;
int block_size, maxfreq, curr_ans, freq[siz+1], inv_freq[siz+10], arr[siz+2]; 

bool comp(query& a,query& b) { //Mo's sol to TSP
    return (a.bn<b.bn) || (a.bn==b.bn &&
    (a.bn&1?a.R<b.R : a.R>b.R) );       //slight optimisation
}

void add(int i) {
	int f = freq[arr[i]];
	inv_freq[f]--;
	if (f==maxfreq) maxfreq++;
	freq[arr[i]]++;
	inv_freq[f+1]++;
}

void remove(int i) {
	int f = freq[arr[i]];
	inv_freq[f]--;
	if (f==maxfreq && inv_freq[f]==0)
		maxfreq--;
	freq[arr[i]]--;
	inv_freq[f-1]++;
}

void solve() {
    int n,q; cin>>n>>q;
    for (int i=0;i<n;i++) cin>>arr[i];
    block_size = max(1, (int) sqrt(n));
    query Q[q];
    int ans[q];
    for (int i=0;i<q;i++) {
        int l,r; cin>>l>>r; 
        Q[i] = {l,r,l/block_size, i};   
    }
    sort(Q, Q+q, comp);
    int l=0, r=-1;
    for (auto i: Q) {
    	int x = i.R-i.L+1;
    	while (r<i.R) {
    		r++;
    		add(r);
    	}
    	while (l>i.L) {
            l--;
            add(l);
        }
        while (r>i.R) {
            remove(r);
            r--;
        }
        while (l<i.L) {
            remove(l);
            l++;
        }
        ans[i.index] = maxfreq;
    }
    for (int i: ans) cout<<i<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    solve();
    return 0;
}