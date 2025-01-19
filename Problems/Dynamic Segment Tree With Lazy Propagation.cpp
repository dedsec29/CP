//https://leetcode.com/problems/my-calendar-iii/

class MyCalendarThree {
    class Node {
    public:
        long long sum, lazy_add, mx;
        Node* left;
        Node* right;

        Node(long long v = 0) : sum(v), lazy_add(0), left(nullptr), right(nullptr), mx(v) {}
    };

    class SegmentTree {
        Node* root;
        int n;

        void push(Node* node,int tl,int tr) {
            if (!node || node->lazy_add == 0)
                return;
            node->sum = node->lazy_add * (tr-tl+1);
            node->mx += node->lazy_add;
            if (tl != tr) { // If not leaf, propagate
                if (!node->left) node->left = new Node();
                if (!node->right) node->right = new Node();
                node->left->lazy_add += node->lazy_add;
                node->right->lazy_add += node->lazy_add;
            }
            node->lazy_add = 0;
        }

        void range_add(Node*& node,int tl,int tr,int l,int r,int x) {
            if (!node) node = new Node();
            push(node, tl, tr);

            if (tr < l || r < tl)
                return;
            if (l <= tl && tr <= r) {
                node->lazy_add += x;
                push(node, tl, tr); // necessary for parent calls for correct combine()
                return;
            }

            int mid = (tl + tr) >> 1;
            range_add(node->left, tl, mid, l, r, x);
            range_add(node->right, mid+1, tr, l, r, x);
            combine_node(node, node->left, node->right);
        }

        long long query(Node* node,int tl,int tr,int l,int r) {
            if (!node || r < tl || tr < l)
                return 0;

            push(node, tl, tr);
            if (l <= tl && tr <= r)
                return node->mx;
            int mid = (tl + tr) >> 1;
            return max( query(node->left, tl, mid, l, r), query(node->right, mid+1, tr, l, r) );
        }

        void combine_node(Node*& node,Node* left,Node* right) {
            node->sum = (left ? left->sum : 0) + (right ? right->sum : 0);
            node->mx = max((left ? left->mx : 0), (right ? right->mx : 0));
        }

    public:

        SegmentTree() : n(0), root(nullptr) {}

        SegmentTree(int size) : n(size), root(nullptr) {}

        void range_add(int l,int r,int x) {
            range_add(root, 0, n-1, l, r, x);
        }

        int query(int l,int r) {
            return query(root, 0, n-1, l, r);
        }
    };

    const int nax = 1e9+1;

    SegmentTree X = SegmentTree(nax);

public:
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        endTime--;
        X.range_add(startTime, endTime, 1);
        return X.query(0, nax-1);
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */