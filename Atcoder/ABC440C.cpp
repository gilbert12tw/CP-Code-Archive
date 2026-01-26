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
    int n, w;
    cin >> n >> w;

    vector<ll> c(n);
    vector<ll> v(2 * w);
    for (ll &i : c) cin >> i;

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        v[i % (2 * w)] += c[i];
        sum += c[i];
    }

    ll tmp = 0;
    for (int i = 0; i < w; i++) tmp += v[i];
    ll ans = min(tmp, sum - tmp);
    for (int i = w; i < 2 * w; i++) {
        tmp += v[i];
        tmp -= v[i - w];
        ans = min(ans, min(tmp, sum - tmp));
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
