// https://judge.yosupo.jp/problem/enumerate_palindromes
// https://www.baeldung.com/cs/manachers-algorithm
// https://cp-algorithms.com/string/manacher.html
#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

vector<int> manacher_odd(string& s) {
    int n = s.size();
    s = "$" + s + "^";  // 1 based indexing
    // for (auto i: s) cout << i << " ";
    // cout << endl;
    vector<int> p(n+2);
    int l = 0, r = -1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r-i, (l+r-i >= 0) ? p[l+r-i] : INT_MAX ) );
        while (s[i - p[i]] == s[i + p[i]])
            p[i]++;
        if (i + p[i] > r) {
            r = i + p[i];
            l = i - p[i];
        }
    }
    // for (auto i: p) cout  << i << " ";
    // cout << endl;
    // for s = "abcbcba"
    // $ # a # b # c # b # c # b # a # ^ 
    // 0 1 2 1 2 1 4 1 8 1 4 1 2 1 2 1 0 
    return vector<int>(p.begin()+1, p.end()-1);
}

vector<int> manacher(string& s) {
    string t = "";              
    // 0  1 2  3 4  5 ...   2n-1 2n
    // # s0 # s1 # s2 ... # sn-1 #  
    for (char c: s) {
        string k = "#";
        k += c;
        t += k;
    }
    // doing this makes even ones odd length
    t += '#';                       // is this crucial?
    vector<int> arr = manacher_odd(t);
    // for s = "abcbcba"
    // # a # b # c # b # c # b # a #
    // 1 2 1 2 1 4 1 8 1 4 1 2 1 2 1 
    // 0 1 2 3 4 5 ..              sz-1
    // odd indices => odd length palindromes, these will always be even, /2 * 2 - 1 => - 1
    // even indices=> even length palindromes, these will always be odd, -1 / 2 * 2 => - 1
    vector<int> d;
    int sz = arr.size();
    for (int i = 1; i < sz-1; i++) 
        d.push_back(arr[i]-1);
    return d;
}

void solve() {
    string s; cin >> s;
    vector<int> arr = manacher(s);
    for (int i: arr) cout << i << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}