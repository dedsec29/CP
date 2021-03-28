#include <bits/stdc++.h>
using namespace std;

struct query {
    int L,R, bn, index;
};

int const siz = 30000; 
int block_size; //Minima of f(B) = QB+N*N/B 
int n, arr[siz+1], curr_ans, freq[siz+1];

bool comp(query& a,query& b) { //Mo's sol to TSP
    return (a.bn<b.bn) || (a.bn==b.bn &&
    (a.bn&1?a.R<b.R : a.R>b.R) );       //slight optimisation
}

void add(int idx) {
    if (++freq[arr[idx]]==1)
        curr_ans++;
}

void remove(int idx) {
    if (--freq[arr[idx]]==0) 
        curr_ans--;
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cin>>n;
    map<int,int> compress;
    for (int i=1;i<=n;i++) {
        cin>>arr[i];
        compress[arr[i]];
    }
    int cp=0;
    for (auto x: compress) 
        compress[x.first] = ++cp;
    for (int i=1;i<=n;i++)
        arr[i] = compress[arr[i]];    //overwriting the orignal array, which has values compress such that freq array can be maintained
    
    int q; cin>>q;
    block_size = max(1, (int) sqrt(n));
    query Q[q];
    int ans[q];
    for (int i=0;i<q;i++) {
        int l,r; cin>>l>>r;
        Q[i] = {l,r,l/block_size, i};   
    }
    sort(Q, Q+q, comp);
    int l=1,r=0; //think of the query 1,1 (ensures correctness of l and r for q1)
    for (auto i: Q) {
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
        ans[i.index] = curr_ans;
    }
    for (int i: ans) cout<<i<<"\n";
    return 0;
}