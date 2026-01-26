#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> pref_max(n), suff_min(n);
    pref_max[0] = a[0];
    for(int i = 1; i < n; i++) {
        pref_max[i] = max(pref_max[i - 1], a[i]);
    }
    suff_min[n - 1] = a[n - 1];
    for(int i = n - 2; i >= 0; i--) {
        suff_min[i] = min(suff_min[i + 1], a[i]);
    }
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        if(pref_max[i] <= a[i] && a[i] <= suff_min[i]) {
            ans.push_back(a[i]);
        }
    }
    cout << ans.size();
    for(int i = 0; i < min((int) ans.size(), 100); i++) {
        cout << " " << ans[i];
    }
    cout << "\n";
    return 0;
}
