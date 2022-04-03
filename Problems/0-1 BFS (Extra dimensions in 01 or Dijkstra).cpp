// https://atcoder.jp/contests/abc246/tasks/abc246_e

#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long
 
vector<int> di = {-1,1,1,-1}; 
vector<int> dj = {-1,-1,1,1};
 
void solve() {
    int n; cin >> n;
    int inf = 1e9;
    int sx,sy; cin >> sx >> sy;
    int tx,ty; cin >> tx >> ty;
    vector<vector<char>> grid(n+1, vector<char>(n+1));
    vector<vector<vector<int>>> dist(n+1, vector<vector<int>>(n+1, vector<int>(4, inf)));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> grid[i][j];
    
    // x,y, direction in last move
    // so we need one more dimension in our dist 
    deque<vector<int>> Q;
    for (int k = 0; k < 4; k++) {
        dist[sx][sy][k] = 0; 
        int u = sx + di[k];
        int v = sy + dj[k];
        if (1 <= u && u <= n && 1 <= v && v <= n && grid[u][v] == '.') {
            dist[u][v][k] = 1;
            Q.push_back({u,v,k});
        }
    }

    while (!Q.empty()) {
        auto x = Q.front()[0];
        auto y = Q.front()[1];
        auto d = Q.front()[2];
        Q.pop_front();
        for (int k = 0; k < 4; k++) {
            int u = x + di[k];
            int v = y + dj[k];
            if (1 <= u && u <= n && 1 <= v && v <= n && grid[u][v] == '.') {
                int wt = (d != k);
                if (dist[x][y][d] + wt < dist[u][v][k]) {
                    dist[u][v][k] = dist[x][y][d] + wt;
                    if (wt)
                        Q.push_back({u,v,k});
                    else
                        Q.push_front({u,v,k});
                }
            }
        }
    }
    int ans = inf;
    for (int k = 0; k < 4; k++) 
        ans = min(ans, dist[tx][ty][k]);
    if (ans >= inf) ans = -1;
    cout << ans;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}