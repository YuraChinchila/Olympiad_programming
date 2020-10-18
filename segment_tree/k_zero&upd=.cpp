#include <bits/stdc++.h>

using namespace std;

vector<int> tree;

inline void updateNode(int v) {
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

void build(int v, int vl, int vr, vector<int> & a) {
    if (vl + 1 == vr) {
        tree[v] = (a[vl] ? 0 : 1);
    } else {
        int vm = (vl + vr) >> 1;
        build(v * 2, vl, vm, a);
        build(v * 2 + 1, vm, vr, a);
        updateNode(v);
    }
}

int getSum(int v, int vl, int vr, int l, int r) {
    if (vl >= r || vr <= l) return 0;
    if (vl >= l && vr <= r) return tree[v];
    int vm = (vl + vr) >> 1;
    return getSum(v * 2, vl, vm, l, r) + getSum(v * 2 + 1, vm, vr, l, r);
}

int findZero(int l, int r, int k, int n) {
    if (getSum(1, 0, n, l, r) < k) return -2;
    if (l + 1 == r) return l;
    int vm = (l + r) >> 1;
    int sum1 = getSum(1, 0, n, l, vm);
    int sum2 = getSum(1, 0, n, vm, r);
    return (sum1 >= k ? findZero(l, vm, k, n) : findZero(vm, r, k - sum1, n));
}

void update(int v, int vl, int vr, int pos, int val) {
    if (vl + 1 == vr) {
        tree[v] = (val ? 0 : 1);
    } else {
        int vm = (vl + vr) >> 1;
        if (pos <= vm) {
            update(v * 2, vl, vm, pos, val);
        } else {
            update(v * 2 + 1, vm, vr, pos, val);
        }
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
    for (int i = 0; i < m; i++) {
        char type;
        cin >> type;
        if (type == 's') {
            int l, r, k;
            cin >> l >> r >> k;
            cout << findZero(l - 1, r, k, n) + 1 << "\n";
        } else {
            int pos, val;
            cin >> pos >> val;
            update(1, 0, n, pos, val);
        }
    }
    return 0;
}