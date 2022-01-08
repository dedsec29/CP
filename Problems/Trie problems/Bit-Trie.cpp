#include <bits/stdc++.h>
using namespace std;

int const word_size = 30;

// we don't literally delete, just make counts to 0
// we can do so only on isEnd, but then we need information if we can
// traverse sameBit or not, so we need cnt on every node
class Bit_Trie {
private:
    struct node {
        node* next[2];
        int cnt = 0;
        node() {
            next[0] = next[1] = NULL;
        } 
    };
    node root;

public:
    void insert(int s) {
        node* temp = &root;
        ++temp->cnt;
        for (int i = word_size-1; i >= 0; i--) {
            int bit = (s >> i) & 1;
            if (temp->next[bit] == NULL)
                temp->next[bit] = new node();
            temp = temp->next[bit];
            ++temp->cnt;
        }
    }

    int query(int a) {
        int ans = 0;  // minimum (a ^ p)
        node* temp = &root;
        --temp->cnt;
        for (int i = word_size-1; i >= 0; i--) {
            int bit = (a & (1<<i)) ? 1 : 0;
            bool sameBit = (temp->next[bit] != NULL && temp->next[bit]->cnt > 0);
            if (sameBit) 
                temp = temp->next[bit];
            else {
                ans |= (1 << i);
                temp = temp->next[bit^1];
            }
            --temp->cnt;
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Bit_Trie X;
    int n; cin >> n;
    vector<int> A(n);
    vector<int> P(n);
    for (int& i: A) cin >> i;
    for (int& i: P) {
        cin >> i;
        X.insert(i);
    }
    for (int i: A) cout << X.query(i) << " ";
    return 0;
}