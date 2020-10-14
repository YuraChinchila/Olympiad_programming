#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0), cout.tie(0);
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int & i : a) {
        cin >> i;
    }
    multiset<int> ms; 
    ms.insert(a[0]); 
    int ans = 0;  
    for (int i = 1; i < n; i++) { 
        ms.insert(a[i]); 
        auto it = ms.upper_bound(a[i]); 
        ans += distance(it, ms.end()); 
    } 
    cout << ans;
    return 0;
}
