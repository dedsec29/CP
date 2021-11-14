#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

vector<vector<int>> build(vector<vector<int>>& grid,int n,int m) {
    vector<vector<int>> pre(grid);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++)
            pre[i][j] += pre[i][j-1];
    for (int i = 1; i <= n; i++) 
        for (int j = m; j >= 1; j--) 
            pre[i][j] += pre[i-1][j];
    return pre;
}

int query(int x1,int y1,int x2,int y2,vector<vector<int>>& pre) {
    return pre[x2][y2] - pre[x2][y1-1] - pre[x1-1][y2] + pre[x1-1][y1-1];
}

void solve() {
    int n,q; cin >> n >> q;
    vector<vector<int>> grid(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            grid[i][j] = (c == '*');
        }
    }
    vector<vector<int>> pre = build(grid,n,n);
    while (q--) {
        int y1,x1,y2,x2; cin >> x1 >> y1 >> x2 >> y2;
        cout << query(x1,y1,x2,y2,pre) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}