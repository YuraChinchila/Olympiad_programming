#include <bits/stdc++.h>

using namespace std;

struct node {
    int ans, suf, pref;
    node(int _ans = 0, int _suf = 0, int _pref = 0) {
        ans = _ans, suf = _suf, pref = _pref;
    }
};

vector<node> tree;

inline void updateNode(int v, int vl, int vm, int vr) {
    node l = tree[v * 2], r = tree[v * 2 + 1];
    tree[v].ans = max({l.ans, r.ans, l.suf + r.pref});
    tree[v].suf = (r.ans == vr - vm ? r.ans + l.suf : r.suf);
    tree[v].pref = (l.ans == vm - vl ? l.ans + r.pref : l.pref);
}

void build(int v, int vl, int vr, vector<int> & a) {
    if (vl + 1 == vr) {
        tree[v] = (a[vl] ? node() : node(1, 1, 1));
    } else {
        int vm = (vl + vr) >> 1;
        build(v * 2, vl, vm, a);
        build(v * 2 + 1, vm, vr, a);
        updateNode(v, vl, vm, vr);
    }
}

node getMaxSeqOfZero(int v, int vl, int vr, int l, int r) {
    if (vl >= r || vr <= l) return node();
    if (vl >= l && vr <= r) return tree[v];
    int vm = (vl + vr) >> 1;
    auto [ans_l, suf_l, pref_l] = getMaxSeqOfZero(v * 2, vl, vm, l, r);
    auto [ans_r, suf_r, pref_r] = getMaxSeqOfZero(v * 2 + 1, vm, vr, l, r);
    node res;
    res.ans = max({ans_l, ans_r, suf_l + pref_r});
    res.suf = (ans_r == vr - vm ? ans_r + suf_l : suf_r);
    res.pref = (ans_l == vm - vl ? ans_l + pref_r : pref_l);
    return res;
}

void update(int v, int vl, int vr, int pos, int val) {
    if (vl + 1 == vr) {
        tree[v] = (val ? node() : node(1, 1, 1));
    } else {
        int vm = (vl + vr) >> 1;
        if (pos <= vm) {
            update(v * 2, vl, vm, pos, val);
        } else {
            update(v * 2 + 1, vm, vr, pos, val);
        }
        updateNode(v, vl, vm, vr);
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
        string type;
        cin >> type;
        if (type[0] == 'Q') {
            int l, r;
            cin >> l >> r;
            cout << getMaxSeqOfZero(1, 0, n, l - 1, r).ans << "\n";
        } else {
            int pos, val;
            cin >> pos >> val;
            update(1, 0, n, pos, val);
        }
    }
    return 0;
}
