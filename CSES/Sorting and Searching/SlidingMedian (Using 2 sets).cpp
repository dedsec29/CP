#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//https://www.youtube.com/watch?v=UGs_kQxJNPk

void add(ll x,multiset<int>& A,multiset<int>& B,int szA,int szB) {
    if (x >= *A.rbegin())
        B.insert(x);
    else
        A.insert(x);
    while ((int)A.size() > szA) {
        B.insert(*A.rbegin());
        A.erase(A.find(*A.rbegin()));
    }
    while ((int)A.size() < szA) {
        A.insert(*B.begin());
        B.erase(B.begin());
    }
}

void answer(multiset<int>& A,multiset<int>& B) {
    cout << *A.rbegin() << " ";
}

void remove(ll x,multiset<int>& A,multiset<int>& B) {
    if (A.find(x) != A.end())
        A.erase(A.find(x));
    else if (B.find(x) != B.end())
        B.erase(B.find(x));
}

void solve() {
    int n,k; cin>>n>>k;
    vector<int> arr(n);
    multiset<int> A, B;  //A median, B   (A includes median)
    int szA = k - k/2;
    int szB = k/2;
    for (int& i: arr) cin >> i;

    if (k == 1) {
        for (int i: arr) cout << i << " ";
        return;
    }
    if (k == 2) {
        for (int i=1;i<n;i++) cout << min(arr[i], arr[i-1]) << " ";
        return;
    }

    vector<int> v(k-1);
    for (int i = 0; i < k-1; i++) v[i] = arr[i];
    sort(v.begin(), v.end());
    for (int i = 0; i < k-1; i++) {
        if (i <= (k-2)/2)
            A.insert(v[i]);
        else
            B.insert(v[i]);
    }

    for (int i = k-1; i < n; i++) {
        add(arr[i], A,B,szA,szB);
        answer(A,B);
        remove(arr[i-k+1], A,B);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}