// https://codeforces.com/contest/1163/problem/C2
// Be careful about overflows. Making inf fraction is tricky because of overflow
// Best to handle 90 degree slopes separately

#include <bits/stdc++.h>
using namespace std;
// #pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

int choose2(int n) {
    return (n * (n-1))>>1;
}

struct Fraction {
    int x, y;

    Fraction() { x = 0, y = 1; }
    Fraction(int _x, int _y) {
        int g = __gcd(llabs(_x), llabs(_y));
        x = _x / g;
        y = _y / g;

        if (y < 0) {
            x = -x;
            y = -y;
        }
    }

    Fraction operator + (const Fraction& a) {
        return Fraction(x*a.y + y*a.x, y*a.y);
    }
    Fraction operator - (const Fraction& a) {
        return Fraction(x*a.y - y*a.x, y*a.y);
    }
    Fraction inverse() {
        return Fraction(y, x);
    }
    Fraction operator * (const Fraction& a) {
        return Fraction(x*a.x, y*a.y);
    }
};

bool operator == (const Fraction& a, const Fraction& b) {
    if (a.x / a.y != b.x / b.y) return false;
    return a.x*b.y == a.y*b.x;
}
bool operator != (const Fraction& a, const Fraction& b) {
    return a.x*b.y != a.y*b.x;
}
bool operator < (const Fraction& a, const Fraction& b) {
    return a.x*b.y < a.y*b.x;
}

void solve() {
    int n; cin >> n;
    set<pair<Fraction,Fraction>> unique_lines;
    map<Fraction, set<Fraction>> slopes;
    set<int> slope90;

    vector<pair<int,int>> arr(n);
    for (auto& i: arr)
        cin >> i.first >> i.second;
    for (int i = 0; i < n; i++) {
        int x1 = arr[i].first, y1 = arr[i].second;
        for (int j = i+1; j < n; j++) {
            int x2 = arr[j].first, y2 = arr[j].second;
            if (x2 == x1) { 
                slope90.insert(x1);
            }
            else {
                Fraction m = Fraction(y2-y1, x2-x1);
                Fraction c = Fraction(y2, 1) - m * Fraction(x2, 1);

                unique_lines.insert({m, c});
                slopes[m].insert(c);
            }
        }
    }

    int ans = choose2(unique_lines.size() + slope90.size()) - choose2(slope90.size());
    for (auto i: slopes) {
        ans -= choose2(i.second.size());
    }
    cout << ans << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}