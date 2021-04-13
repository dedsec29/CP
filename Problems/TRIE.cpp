#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
//https://codedrills.io/contests/amrita-icpc-practice-session-6/problems/optimal-data-transfer
#define ll long long

struct node {
    bool leaf;  //true if leaf (extra node indicating end)
    node* ar[2];
};

node* createNode() {
    node* newNode = new node;
    newNode->leaf = false;
    for (int i=0;i<2;i++)
        newNode->ar[i] = NULL;
    return newNode; 
}

void insert(node* v,const string& s) {
    node* temp = v;
    for (char c: s) {
        int idx = c-'0';
        if (temp->ar[idx]==NULL) 
            temp->ar[idx] = createNode();
        temp = temp->ar[idx];
    }
    temp->leaf = true;
}

ll getCount(node* v) {
    if (v->leaf)
        return 0;
    ll ans = 0;
    for (int i=0;i<2;i++) {
        if (v->ar[i]!=NULL)
            ans += 1ll + getCount(v->ar[i]);
    }
    return ans;
}

void solve() {
    int n,m; cin>>n>>m;
    node* root = createNode();
    for (int i=0;i<n;i++) {
        string s; cin>>s;
        insert(root, s);
    }    
    // number of distinct prefixes = number of nodes in trie
    cout<<getCount(root)<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}