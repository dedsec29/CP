#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,k; cin>>n>>m>>k;
    ll applicants[n], appartments[m];
    for (int i=0;i<n;i++) cin>>applicants[i];
    for (int i=0;i<m;i++) cin>>appartments[i];
    int ans = 0;
    sort(appartments, appartments+m);
    sort(applicants, applicants+n);
    
    for (int l=0,r=0;r<m && l<n;r++) {
        if (applicants[l]-k <= appartments[r]) {
            if (appartments[r] <= applicants[l]+k) 
                ans++;
            else 
                r--;
            l++;
        }
    }
    cout<<ans<<"\n";
    return 0;
}