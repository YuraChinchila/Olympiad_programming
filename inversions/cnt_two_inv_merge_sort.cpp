#include <bits/stdc++.h>

using namespace std;

int merge(vector<int> & a, vector<int> & tmp, int l, int mid, int r) {
    int i = l, j = mid, k = l, res = 0;
    while (i < mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            res += mid - i;
        }
    }
    while (i < mid) {
        tmp[k++] = a[i++];
    }
    while (j <= r) {
        tmp[k++] = a[j++];
    }
    for (i = l; i <= r; i++) {
        a[i] = tmp[i];
    }
    return res;
}


int mergeSort(vector<int> & a, vector<int> & tmp, int l, int r) {
    int res = 0;
    if (r > l) {
        int mid = (r + l) >> 1;
        res += mergeSort(a, tmp, l, mid);
        res += mergeSort(a, tmp, mid + 1, r);
        res += merge(a, tmp, l, mid + 1, r);
    }
    return res;
}

int main() {
    cin.tie(0), cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n), tmp(n);
    for (int & i : a) {
        cin >> i;
    }
    cout << mergeSort(a, tmp, 0, n - 1);
    return 0;
}
