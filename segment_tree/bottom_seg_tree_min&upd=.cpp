#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> tree;

void build(vector<int> & a) {
    for (int i = 0; i < n; i++) {
        tree[n + i] = a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
    }
}

int getMin(int l, int r) {
    int res = INT_MAX;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            res = min(res, tree[l++]);
        }
        if (r & 1) {
            res = min(res, tree[--r]);
        }
    }
    return res;
}

void update(int pos, int val) {
    tree[pos += n] = val;
    for (int i = pos; i > 1; i >>= 1) {
        tree[i >> 1] = min(tree[i], tree[i ^ 1]);
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> n;
    vector<int> a(n);
    for (int & i : a) {
        cin >> i;
    }
    tree.resize(n * 2, INT_MAX);
    build(a);
    int m;
    cin >> m;
    for (int i = 0, type; i < m; i++) {
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << getMin(l - 1, r) << "\n";
        } else {
            int pos, val;
            cin >> pos >> val;
            update(pos - 1, val);
        }
    }
    return 0;
}
