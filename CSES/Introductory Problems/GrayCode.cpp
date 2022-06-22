#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

vector<int> work(int n) {
    if (n == 0)
        return {0};
    auto A = work(n-1);
    auto B = A;
    reverse(B.begin(), B.end());
    for (int& i: B)
        i |= 1<<(n-1);
    A.insert(A.end(), B.begin(), B.end());
    return A;
}

void solve() {  // exploit the reflection property
    // construct answer by turning bit on of f(i-1)
    int n; cin >> n;
    auto arr = work(n);
    for (int i: arr) {
        for (int j = n-1; j >= 0; j--) 
            cout << ( (i&(1<<j)) ? 1 : 0 );
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}