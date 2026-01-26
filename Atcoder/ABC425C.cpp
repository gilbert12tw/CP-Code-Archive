#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define int long long
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
    vector<int> a(n), pre(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i == 0) pre[i] = a[i];
        else pre[i] = pre[i-1] + a[i];
    }

    auto get = [&](int l, int r) -> int {
        if (l <= r) {
            return pre[r] - (l == 0 ? 0 : pre[l-1]);
        } 
        return pre[r] + pre[n-1] - (l == 0 ? 0 : pre[l-1]);
    };

    int bias = 0;
    while (q--) {
        int o, l, r, c;
        cin >> o;
        if (o == 1) {
            cin >> c;
            bias = (bias + c) % n;
        } else {
            cin >> l >> r;
            l--, r--;
            l = (l + bias) % n;
            r = (r + bias) % n;
            cout << get(l, r) << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
