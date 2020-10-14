#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> tree;

int getSum(int k, int x) {
    int res = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1) {
        res += tree[k][x];
    }
    return res;
}

void update(int k, int pos, int val) {
    int n = tree[k].size();
    for (; pos < n; pos |= pos + 1) {
        tree[k][pos] += val;
    }
}

int main() {
	cin.tie(0), cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int & i : a) {
        cin >> i;
    }
    vector<int> e = a;
    sort(e.begin(), e.end());
    e.erase(unique(e.begin(), e.end()), e.end());
    for (int & i : a) {
        i = lower_bound(e.begin(), e.end(), i) - e.begin();
    }
    int m = e.size();
    tree.resize(k, vector<int> (m));
    for (int i = n - 1; i >= 0; i--) {
        update(0, a[i], 1);
        for (int l = 0; l < k - 1; l++) {
            update(l + 1, a[i], getSum(l, a[i] - 1));
        }
    }
    cout << getSum(k - 1, m - 1);
    return 0;
}
