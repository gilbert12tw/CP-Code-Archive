#include<bits/stdc++.h>
using namespace std;

int main () {
    int t; cin >> t;
    while (t--) {
        long long w, b; cin >> w >> b;
        long long ans = 0;
        while ((ans + 2) * (ans + 1) / 2 <= w + b) ans++;
        cout << ans << '\n';
    }
    return 0;
}
