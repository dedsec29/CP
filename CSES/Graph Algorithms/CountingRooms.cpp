#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin>>n>>m;
    char grid[n+1][m+1];
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) cin>>grid[i][j];
    bool vis[n+1][m+1];
    int rooms=0;
    memset(vis, false, sizeof vis);
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            if (grid[i][j]=='#' || vis[i][j]) continue;
            rooms++;
            vis[i][j]=true;
            queue<pair<int,int>> Q;
            Q.push({i,j});
            while (!Q.empty()) {
                auto a=Q.front();
                int x=a.first, y=a.second;
                Q.pop();
                if (x!=1 && grid[x-1][y]=='.' && !vis[x-1][y]) vis[x-1][y]=true, Q.push({x-1,y});
                if (y!=1 && grid[x][y-1]=='.' && !vis[x][y-1]) vis[x][y-1]=true, Q.push({x,y-1});
                if (x!=n && grid[x+1][y]=='.' && !vis[x+1][y]) vis[x+1][y]=true, Q.push({x+1,y});
                if (y!=m && grid[x][y+1]=='.' && !vis[x][y+1]) vis[x][y+1]=true, Q.push({x,y+1});
            }
        }
    }
    cout<<rooms;
    return 0;
}