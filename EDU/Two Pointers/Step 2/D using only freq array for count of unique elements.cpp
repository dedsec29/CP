#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e5;
int freq[siz+1];

void add(int x,int arr[],int& num) {
    if (freq[x] == 0)
        num++;
    freq[x]++;
}

void remove(int x,int arr[],int& num) {
    if (freq[x] == 1)
        num--;
    freq[x]--;
}

void solve() {
    int n,k; cin>>n>>k;
    int arr[n];
    for (int i=0;i<n;i++) cin>>arr[i];
    int num = 0;
    ll ans = 0;
    for (int l=0,r=0;r<n;r++) {
        add(arr[r],arr,num);
        while (num > k) {
            remove(arr[l],arr,num);
            l++;
        }
        ans += (ll) r-l+1;  //fixing right borders
    }
    cout<<ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}