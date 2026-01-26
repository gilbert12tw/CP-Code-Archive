#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    ll l, r;
    cin >> l >> r;  

    auto is_pa = [](ll x) -> bool {
        auto s = to_string(x);
        auto rs = s;
        reverse(rs.begin(), rs.end());
        return s == rs;
    };
    
    auto is_pr = [](ll x) -> bool {
        if (x == 1) return false;
        for (ll i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    };

    bool first = true;
    for (ll i = l; i <= r; i++) {
        if (!is_pa(i)) continue;
        if (!is_pr(i)) continue;
        if (first) {
            first = false;
        } else {
            cout << " ";
        }
        cout << i;
    }
    if (first) cout << "None";
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
