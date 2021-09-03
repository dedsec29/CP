#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define int long long

void add(int x,multiset<int>& A,multiset<int>& B,int szA,int& sumA,int& sumB) {
    if (x >= *A.rbegin()) {
        B.insert(x);
        sumB += x;
    }
    else {
        A.insert(x);
        sumA += x;
    }
    while ((int)A.size() > szA) {
        sumB += *A.rbegin();
        sumA -= *A.rbegin();
        B.insert(*A.rbegin());
        A.erase(A.find(*A.rbegin()));
    }
    while ((int)A.size() < szA) {
        sumA += *B.begin();
        sumB -= *B.begin();
        A.insert(*B.begin());
        B.erase(B.begin());
    }
}

void answer(multiset<int>& A,multiset<int>& B,int sumA,int sumB) {
    int q1 = A.size(), q2 = B.size();
    int median = *A.rbegin();
    cout << median*q1 - sumA + sumB - median*q2 << " ";
}

void remove(int x,multiset<int>& A,multiset<int>& B,int& sumA,int& sumB) {
    if (A.find(x) != A.end()) {
        sumA -= x;
        A.erase(A.find(x));
    }
    else if (B.find(x) != B.end()) {
        sumB -= x;
        B.erase(B.find(x));
    }
}

void solve() {
    int n,k; cin>>n>>k;
    vector<int> arr(n);
    multiset<int> A, B;  //A median, B   (A includes median)
    int szA = k - k/2;
    for (int& i: arr) cin >> i;

    if (k == 1) {
        for (int i: arr) cout << "0 ";
        return;
    }
    if (k == 2) {
        for (int i=1;i<n;i++) cout << abs(arr[i]-arr[i-1]) << " ";
        return;
    }

    vector<int> v(k-1);
    int sumA = 0, sumB = 0;
    for (int i = 0; i < k-1; i++) v[i] = arr[i];
    sort(v.begin(), v.end());
    for (int i = 0; i < k-1; i++) {
        if (i <= (k-2)/2) {
            A.insert(v[i]);
            sumA += v[i];
        }
        else {
            B.insert(v[i]);
            sumB += v[i];
        }
    }

    for (int i = k-1; i < n; i++) {
        add(arr[i], A,B,szA, sumA,sumB);
        answer(A,B,sumA,sumB);
        remove(arr[i-k+1], A,B, sumA,sumB);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}