https://www.youtube.com/watch?v=oib-XsjFa-M&t=14s

class TreeAncestor {
    vector<vector<int>> up;
public:
    TreeAncestor(int n, vector<int>& parent) {
        int ub = __lg(n) + 1;
        up = vector<vector<int>>(n, vector<int>(ub+1));
        for (int i=0;i<n;i++)
            up[i][0] = parent[i];
        for (int j=1;j<=ub;j++) {
            for (int i=0;i<n;i++) {
                if (up[i][j-1]==-1)
                    up[i][j] = -1;
                else
                    up[i][j] = up[ up[i][j-1] ][j-1];   
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for (int i=0;k!=0;i++,k>>=1) {
            if (k&1) {
                if (up[node][i]==-1)
                    return -1;
                node = up[node][i];
            }
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */