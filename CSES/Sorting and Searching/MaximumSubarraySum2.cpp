#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//author: @dedsec_29
template <typename T>
struct minimum_queue {
    stack<pair<T,T>> s2, s1; // ---(s2----||s1---)---
    //add new elements to s1, remove elements from s2
    minimum_queue() {
        s1 = stack<pair<T,T>>();
        s2 = stack<pair<T,T>>(); 
    }

    T getMinimum() {
        T minimum;
        if (s1.empty() || s2.empty())
            minimum = s1.empty() ? s2.top().second : s1.top().second;
        else
            minimum = min(s1.top().second, s2.top().second);
        return minimum;
    }

    void push(T new_element) {
        T minimum = s1.empty() ? new_element : min(new_element, s1.top().second);
        s1.push({new_element, minimum});
    }

    void pop() {
        if (s2.empty()) {
            assert(!s1.empty());
            while (!s1.empty()) {
                T element = s1.top().first;
                s1.pop();
                T minimum = s2.empty() ? element : min(element, s2.top().second);
                s2.push({element, minimum});
            }
        }
        s2.pop();
    }
};

void solve() {
    int n,a,b; cin>>n>>a>>b;
    vector<ll> arr(n+1), pre(n+1);
    for (int i=1;i<=n;i++) {
        cin>>arr[i];
        pre[i] = pre[i-1] + arr[i];
    }
    minimum_queue<ll> Q;
    Q.push(0);
    ll ans = pre[a];
    for (int i=a+1;i<=n;i++) {
        Q.push(pre[i-a]);
        if (i-b >= 1) 
            Q.pop();
        ans = max(ans, pre[i] - Q.getMinimum());
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}