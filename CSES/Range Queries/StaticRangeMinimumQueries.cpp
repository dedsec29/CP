#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 2e5;
int arr[siz], sparse[siz][__lg(siz)+1];

void buildSparseTable(int n) {
    int ub = __lg(n);
    for (int i=0;i<n;i++)
        sparse[i][0] = arr[i];
    for (int j=1;j<=ub;j++)
        for (int i=0;i+(1<<j)-1<n;i++)
            sparse[i][j] = min(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
}

int query(int l,int r) {
    int interval = r-l+1;
    int jump = __lg(interval);
    return min(sparse[l][jump], sparse[r-(1<<jump)+1][jump]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q; cin>>n>>q;
    for (int i=0;i<n;i++) cin>>arr[i];
    buildSparseTable(n);
    while (q--) {
        int l,r; cin>>l>>r; l--,r--;
        cout<<query(l,r)<<"\n";
    }
    return 0;
}