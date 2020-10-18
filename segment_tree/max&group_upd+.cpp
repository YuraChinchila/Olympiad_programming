#include <bits/stdc++.h>

using namespace std;

struct node {
    int max;
    long long add;
};

vector<node> tree;

inline void updateNode(int v) {
    tree[v].max = max(tree[v * 2].max, tree[v * 2 + 1].max);
}

inline void push(int v) {
    if (tree[v].add) {
        tree[v * 2].add += tree[v].add;
        tree[v * 2 + 1].add += tree[v].add;
        tree[v * 2].max += tree[v].add;
        tree[v * 2 + 1].max += tree[v].add;
        tree[v].add = 0;
    }
}

void build(int v, int vl, int vr, vector<int> & a) {
    if (vl + 1 == vr) {
        tree[v].max = a[vl];
    } else {
        int vm = (vl + vr) >> 1;
        build(v * 2, vl, vm, a);
        build(v * 2 + 1, vm, vr, a);
        updateNode(v);
    }
}

int getMax(int v, int vl, int vr, int l, int r) {
    if (vl >= r || vr <= l) return INT_MIN;
    if (vl >= l && vr <= r) return tree[v].max;
    int vm = (vl + vr) >> 1;
    push(v);
    return max(getMax(v * 2, vl, vm, l, r), getMax(v * 2 + 1, vm, vr, l, r));
}

void update(int v, int vl, int vr, int l, int r, int val) {
    if (vl >= r || vr <= l) return;
    if (vl >= l && vr <= r) {
        tree[v].max += val;
        tree[v].add += val;
    } else {
        int vm = (vl + vr) >> 1;
        push(v);
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
    tree.resize(n * 4, {INT_MIN, 0});
    build(1, 0, n, a);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;
        int l, r;
        cin >> l >> r;
        l--;
        if (type == 'm') {
            cout << getMax(1, 0, n, l, r) << " ";
        } else {
            int val;
            cin >> val;
            update(1, 0, n, l, r, val);
        }
    }
    return 0;
}
