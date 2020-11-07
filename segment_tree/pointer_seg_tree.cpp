#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
	node *l, *r;
	int vl, vr;
	ll sum, add;

	node(int _vl, int _vr) {
		l = r = nullptr;
		vl = _vl, vr = _vr;
		sum = add = 0;
	}

	void updNode() {
		sum = l->sum + r->sum;
	}

	void push() {
		l->add += add;
		r->add += add;
		l->sum += add * (l->vr - l->vl);
		r->sum += add * (r->vr - r->vl);
		add = 0;
	}

	void check() {
		if (!l) {
			int vm = (vl + vr) >> 1;
			l = new node(vl, vm);
			r = new node(vm, vr);
		}
	}

	ll getSum(int ql, int qr) {
		if (vl >= qr || vr <= ql) return 0;
		if (vl >= ql && vr <= qr) return sum;
		check();
		push();
		return l->getSum(ql, qr) + r->getSum(ql, qr);
	}

	void update(int ql, int qr, int val) {
		if (vl >= qr || vr <= ql) return;
		if (vl >= ql && vr <= qr) {
			add += val;
			sum += val * (vr - vl);
		} else {
			check();
			push();
			l->update(ql, qr, val);
			r->update(ql, qr, val);
			updNode();
		}
	}

	~node() {
		delete l;
		delete r;
	}
};

int main() {
	cin.tie(0), cout.tie(0);
    ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	node *root = new node(0, n);
	while (m--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r, val;
			cin >> l >> r >> val;
			root->update(l - 1, r, val);
		} else {
			int l, r;
			cin >> l >> r;
			cout << root->getSum(l - 1, r) << "\n";
		}
	}
	return 0;
}
