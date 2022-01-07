#include <bits/stdc++.h>
using namespace std;
//https://codeforces.com/contest/455/problem/B

class Trie {
private:
    static const int al = 26;
    struct node {
        bool isEnd; // true if end of some word
        node* next[al];
        bool FW, FL;    // force win, force lose

        node() {
            for (int i = 0; i < al; i++)
                next[i] = NULL;
            FW = FL = isEnd = false;
        } 
    };
    node root;

public:
    void insert(const string& s) {
        node* temp = &root;
        for (char c: s) {
            if (temp->next[c-'a'] == NULL) 
                temp->next[c-'a'] = new node();
            temp = temp->next[c-'a'];
        }
        temp->isEnd = true;
    }

    void solve() {
        node* temp = &root;
        dfs(temp);
    }

    void dfs(node* v) {
        // if I write a letter, I can push the second player to a losing state?
        // if yes, then current player wins
        if (v->isEnd)
            v->FL = true;
        for (int i = 0; i < al; i++) {
            if (v->next[i] != NULL) {
                dfs(v->next[i]);
                v->FW |= !v->next[i]->FW; 
                v->FL |= !v->next[i]->FL;
            }
        }
    }

    string winner(int k) {
        bool first = false;
        bool FW = root.FW;
        bool FL = root.FL;
        if (FW) {
            if (FL) 
                first = true;
            else {
                if (k&1)
                    first = true;
            }
        }
        return (first) ? "First" : "Second";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // FW[v] = true if above prefix been typed by prev player, now current player can force a win
    int n,k; cin >> n >> k;
    Trie X;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        X.insert(s);
    }
    X.solve();
    cout << X.winner(k);
    return 0;
}