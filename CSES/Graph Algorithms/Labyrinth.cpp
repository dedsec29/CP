#include <bits/stdc++.h>
using namespace std;

char grid[1000][1000];
bool vis[1000][1000];
vector<char> v;
int n,m, sx,sy,dx,dy,d[1000][1000];
pair<int,int> parent[1000][1000];

bool can(int x,int y) {
    if (x==-1 || x==n || y==-1 || y==m)
        return false;
    else {
        if (vis[x][y] || grid[x][y]=='A' || grid[x][y]=='#')
            return false;
        return true;
    }
}

void findShortestDistance() {
    d[sx][sy]=0;
    pair<int,int> sourcep={-1,-1};
    parent[sx][sy]=sourcep;
    queue<pair<int,int>> Q;
    vis[sx][sy]=true;
    Q.push({sx,sy});
    while (!Q.empty()) {
        int i=Q.front().first;
        int j=Q.front().second;
        if (i==dx && j==dy) break;
        Q.pop();
        if (can(i-1,j)) {
            vis[i-1][j]=true;
            d[i-1][j]=d[i][j]+1;
            Q.push({i-1,j});
            parent[i-1][j]= {i,j};
        }
        if (can(i+1,j)) {
            vis[i+1][j]=true;
            d[i+1][j]=d[i][j]+1;
            Q.push({i+1,j});
            parent[i+1][j]= {i,j};
        }
        if (can(i,j-1)) {
            vis[i][j-1]=true;
            d[i][j-1]=d[i][j]+1;
            Q.push({i,j-1});
            parent[i][j-1]= {i,j};
        }
        if (can(i,j+1)) {
            vis[i][j+1]=true;
            d[i][j+1]=d[i][j]+1;
            Q.push({i,j+1});
            parent[i][j+1]= {i,j};
        }
    }
    if (d[dx][dy]==-1) {
        cout<<"NO"; return;
    }
    int i= dx, j= dy;
    while (parent[i][j]!=sourcep) {
        int x= parent[i][j].first;
        int y= parent[i][j].second;
        if (x==i) v.push_back((y>j)?'L':'R');
        else v.push_back((x<i)?'D':'U');
        i=x, j=y;
    }
    cout<<"YES\n"<<v.size()<<"\n";
    for (int i=v.size()-1;i>=0;i--) cout<<v[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n>>m;
    for (int i=0;i<n;i++) for (int j=0;j<m;j++) {
        char c; cin>>c;
        grid[i][j]=c;
        d[i][j]=-1;
        if (c=='A') sx=i, sy=j;
        if (c=='B') dx=i, dy=j;
    }
    findShortestDistance();
    return 0;
}