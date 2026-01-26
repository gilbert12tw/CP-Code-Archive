#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define eb emplace_back
#define ALL(a) a.begin(), a.end()
#define SZ(a) ((int)a.size())

#ifdef debug
template <typename T>
ostream& operator << (ostream &o, vector<T> vec) {
    o << "{"; int f = 0; for (T i : vec) o << (f++ ? " " : "") << i; return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m"; (..., (cerr << a << " ")); cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#endif

void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll &i : a) cin >> i;
    sort(ALL(a));

    auto check = [&a](ll pos, ll x) -> ll {
        ll cnt = upper_bound(ALL(a), pos) - lower_bound(ALL(a), x);
        return pos - x - cnt + 1;
    };

    for (int i = 0; i < q; i++) {
        ll x, y;
        cin >> x >> y;
        ll l = x - 1, r = 1e15;
        while (l < r) {
            ll mid = (l + r + 1) / 2;
            if (check(mid, x) < y) l = mid;
            else r = mid - 1;
        }
        cout << l + 1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
