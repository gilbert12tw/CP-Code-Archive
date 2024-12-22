#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll N = 1e6 + 5;
ll n = 999, a, b;
ll ans[N];

int main () {
    cin >> a >> b;
    for (ll i = 0;i < n; ++i) {
        ans[i] = b;
    }
    if (n*a-n*b > 0) {
        ans[n-1] += n*a-n*b;
    } else if (n*a-n*b < 0) {
        ans[0] += n*a-n*b;
    }
    cout << n << "\n";
    for (ll i = 0;i < n; ++i) {
        cout << ans[i] << " \n"[i==n-1];
    }
    return 0;
}
