#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
	return (b ? gcd(b, a % b) : a);
}

vector<int> tree;

inline void updateNode(int v) {
	tree[v] = gcd(tree[v * 2], tree[v * 2 + 1]);
}

void build(int v, int vl, int vr, vector<int> & a) {
	if (vl + 1 == vr) {
		tree[v] = a[vl];
	} else {
		int vm = (vl + vr) >> 1;
		build(v * 2, vl, vm, a);
		build(v * 2 + 1, vm, vr, a);
		updateNode(v);
	}
}

int getGcd(int v, int vl, int vr, int l, int r) {
	if (vl >= r || vr <= l) return 0;
	if (vl >= l && vr <= r) return tree[v];
	int vm = (vl + vr) >> 1;
	return gcd(getGcd(v * 2, vl, vm, l, r), getGcd(v * 2 + 1, vm, vr, l, r));
}

void update(int v, int vl, int vr, int pos, int val) {
    if (vl + 1 == vr) {
        tree[v] += val;
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
    for (int i = 0, type; i < m; i++) {
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << getGcd(1, 0, n, l - 1, r) << "\n";
        } else {
            int pos, val;
            cin >> pos >> val;
            update(1, 0, n, pos, val);
        }
    }
	return 0;
}
