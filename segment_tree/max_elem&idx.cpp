#include <bits/stdc++.h>

using namespace std;

struct node {
    int max, idx;
    bool operator<(const node & a) const {
        return max < a.max;
    }
};

vector<node> tree;

void build(int v, int vl, int vr, vector<int> & a) {
    if (vl + 1 == vr) {
        tree[v] = {a[vl], vl};
    } else {
        int vm = (vl + vr) >> 1;
        build(2 * v, vl, vm, a);
        build(2 * v + 1, vm, vr, a);
        tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
    }
}

node getMax(int v, int vl, int vr, int l, int r) {
    if (vl >= r || vr <= l) return {INT_MIN, -1};
    if (vl >= l && vr <= r) return tree[v];
    int vm = (vl + vr) >> 1;
    node ans_l = getMax(v * 2, vl, vm, l, r);
    node ans_r = getMax(v * 2 + 1, vm, vr, l, r);
    return max(ans_l, ans_r);
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
    tree.resize(4 * n);
    build(1, 0, n, a);
    int m;
    cin >> m;
    for (int i = 0, l, r; i < m; i++) {
        cin >> l >> r;
        node ans = getMax(1, 0, n, l - 1, r);
        cout << ans.max << " " << ans.idx + 1 << "\n";
    }
    return 0;
}

