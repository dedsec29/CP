#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize "trapv"
#define ll long long

int basis[31]; // basis[i] keeps the mask of the vector whose f value is i

void insertVector(int mask,int k,int& sz) {//k dimensions, mask of vi vector  
    for (int i=0;i<k;i++) {
        if ((mask&(1<<i))==0)
            continue; //when mask has set bit at i 
        if (!basis[i]) {    //no way to make this set with any linear combination, so add to basis
            basis[i] = mask;
            sz++;
            return;
        }
        //when basis for this f() already exists, find if linear comb with vi-b1 now
        mask ^= basis[i]; //subtracting bits
    }
}

void solve() {
    int k, m; cin>>k>>m;
    for (int i=0;i<k;i++) basis[i]=0;
    int arr[m], sz=0;
    for (int i=0;i<m;i++) {
        cin>>arr[i];
        insertVector(arr[i],k,sz);
    }
    cout<<(1<<k)/(1<<sz)<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}