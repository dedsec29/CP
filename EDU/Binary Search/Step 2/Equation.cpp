#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ld long double

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ld c; cin>>c;
    ld l=0, r=c+1;
    for (int i=0;i<100;i++) {
        ld mid = (l+r)/2;
        ld a = sqrt(mid), b = mid*mid;
        if ((a+b)<=c) l=mid;
        else r=mid;
    }
    cout<<fixed<<setprecision(6)<<l;
    return 0;
}