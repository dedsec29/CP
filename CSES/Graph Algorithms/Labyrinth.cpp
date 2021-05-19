#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

vector<int> di = {-1, 1, 0, 0};
vector<int> dj = {0, 0, -1, 1};
vector<char> direc = {'D', 'U', 'R', 'L'};
int const inf = 1e7;

void solve() {
    int n,m; cin>>n>>m;
    int startx, starty;
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<int>> distM(n, vector<int>(m, inf));
    vector<vector<int>> distP(n, vector<int>(m, inf));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m));
    queue<pair<int,int>> Q;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            cin>>grid[i][j];
            if (grid[i][j]=='M') {
                Q.push({i,j});
                distM[i][j] = 0;
            }
            if (grid[i][j]=='A')
                startx = i, starty = j;
        }
    }
    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        for (int z=0;z<4;z++) {
            int i = x + di[z];
            int j = y + dj[z];
            if (i==-1 || j==-1 || i==n || j==m || grid[i][j]=='#') continue;
            if (distM[i][j]==inf) {
                distM[i][j] = distM[x][y] + 1;
                Q.push({i,j});
            }
        }
    }
    Q.push({startx,starty});
    distP[startx][starty] = 0;
    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        for (int z=0;z<4;z++) {
            int i = x + di[z];
            int j = y + dj[z];
            if (i==-1 || j==-1 || i==n || j==m || grid[i][j]=='#') continue;
            if (distP[i][j]==inf) {
                distP[i][j] = distP[x][y] + 1;
                parent[i][j] = {x,y};
                Q.push({i,j});
            }
        }
    }
    int gx = -1, gy = -1, len = 0;
    for (int i=0;i<m;i++) {
        if ((grid[0][i]=='.' || grid[0][i]=='A') && distP[0][i] < distM[0][i]) {
            gx = 0, gy = i;
            len = distP[0][i];
            break;
        }
        if ((grid[n-1][i]=='.' || grid[n-1][i]=='A') && distP[n-1][i] < distM[n-1][i]) {
            gx = n-1, gy = i;
            len = distP[n-1][i];
            break;
        }
    }
    for (int i=0;i<n;i++) {
        if ((grid[i][0]=='.' || grid[i][0]=='A') && (distP[i][0] < distM[i][0])) {
            gx = i, gy = 0;
            len = distP[i][0];
            break;
        }
        if ((grid[i][m-1]=='.' || grid[i][m-1]=='A') && distP[i][m-1] < distM[i][m-1]) {
            gx = i, gy = m-1;
            len = distP[i][m-1];
            break;
        }
    }
    if (gx==-1 && gy==-1) {
        cout<<"NO\n";
        return;
    }
    cout<<"YES\n"<<len<<"\n";
    int x = gx, y = gy;
    string directions = "";
    while (x!=startx || y!=starty) {
        for (int z=0;z<4;z++) {
            int i = x + di[z];
            int j = y + dj[z];
            if (parent[x][y] == make_pair(i,j)) {
                directions += direc[z];
                x = i;
                y = j;
                break;
            }
        }
    }
    reverse(directions.begin(),directions.end());
    cout<<directions;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
