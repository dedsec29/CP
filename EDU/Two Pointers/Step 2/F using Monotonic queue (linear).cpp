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

template <typename T>
struct maximum_queue {
    stack<pair<T,T>> s2, s1; // ---(s2----||s1---)---
    //add new elements to s1, remove elements from s2
    maximum_queue() {
        s1 = stack<pair<T,T>>();
        s2 = stack<pair<T,T>>(); 
    }

    T getMaximum() {
        T maximum;
        if (s1.empty() || s2.empty())
            maximum = s1.empty() ? s2.top().second : s1.top().second;
        else
            maximum = max(s1.top().second, s2.top().second);
        return maximum;
    }

    void push(T new_element) {
        T maximum = s1.empty() ? new_element : max(new_element, s1.top().second);
        s1.push({new_element, maximum});
    }

    void pop() {
        if (s2.empty()) {
            assert(!s1.empty());
            while (!s1.empty()) {
                T element = s1.top().first;
                s1.pop();
                T maximum = s2.empty() ? element : max(element, s2.top().second);
                s2.push({element, maximum});
            }
        }
        s2.pop();
    }
};

void solve() {
    int n; ll k; cin>>n>>k;
    vector<ll> arr(n);
    for (ll& i: arr) cin>>i;
    ll ans = 0;
    minimum_queue<ll> Q_min;
    maximum_queue<ll> Q_max;
    for (int l=0,r=0;r<n;r++) {
        Q_min.push(arr[r]);
        Q_max.push(arr[r]);
        while (Q_max.getMaximum() - Q_min.getMinimum() > k) {
            Q_min.pop();
            Q_max.pop();
            l++;
        }
        ans += (ll) r-l+1;
    }
    cout<<ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}