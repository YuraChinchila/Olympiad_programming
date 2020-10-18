#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
    ll sum, add;
};

vector<node> tree;

inline void updateNode(int v) {
    tree[v].sum = tree[v * 2].sum + tree[v * 2 + 1].sum;
}

inline void push(int v, int vl, int vm, int vr) {
    if (tree[v].add) {
        tree[v * 2].add += tree[v].add;
        tree[v * 2 + 1].add += tree[v].add;
        tree[v * 2].sum += (vm - vl) * tree[v].add;
        tree[v * 2 + 1].sum += (vr - vm) * tree[v].add;
        tree[v].add = 0;
    }
}

void build(int v, int vl, int vr, vector<int> & a) {
    if (vl + 1 == vr) {
        tree[v] = {a[vl], 0};
    } else {
        int vm = (vl + vr) >> 1;
        build(v * 2, vl, vm, a);
        build(v * 2 + 1, vm, vr, a);
        updateNode(v);
    }
}

ll getSum(int v, int vl, int vr, int l, int r) {
    if (vl >= r || vr <= l) return 0;
    if (vl >= l && vr <= r) return tree[v].sum;
    int vm = (vl + vr) >> 1;
    push(v, vl, vm, vr);
    return getSum(v * 2, vl, vm, l, r) + getSum(v * 2 + 1, vm, vr, l, r);
}

void update(int v, int vl, int vr, int l, int r, int val) {
    if (vl >= r || vr <= l) return;
    if (vl >= l && vr <= r) {
        tree[v].add += val;
        tree[v].sum += (vr - vl) * val;
    } else {
        int vm = (vl + vr) >> 1;
        push(v, vl, vm, vr);
        update(v * 2, vl, vm, l, r, val);
        update(v * 2 + 1, vm, vr, l, r, val);
        updateNode(v);
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int & i : a) {
        cin >> i;
    }
    tree.resize(n * 4);
    build(1, 0, n, a);
    int m;
    cin >> m;
    for (int i = 0, type; i < m; i++) {
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << getSum(1, 0, n, l - 1, r) << "\n";
        } else {
            int l, r, s;
            cin >> l >> r >> s;
            update(1, 0, n, l - 1, r, s);
        }
    }
    return 0;
}
