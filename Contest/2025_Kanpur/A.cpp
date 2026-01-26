#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
#define vi vector<int>
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - x.begin())
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
template <typename... T> void _print(T... args) {
    ((cerr << args << ' '), ...);
    cerr << '\n';
}
#ifdef debug
#define test(args...) _print("[" + string(#args) + "]:", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    int suma = 0, sumb = 0;
    for (int &i : a) {
        cin >> i;
        suma += i;
    }
    for (int &i : b) {
        cin >> i;
        sumb += i;
    }
    if (suma != sumb) {
        cout << -1 << '\n';
        return;
    }
    
    vector<int> cc(2, 0);
    for (int i = 0; i < n; i++) {
        cc[abs(a[i] - b[i]) % 2]++;
    }
    if (cc[0] > 0 && cc[1] > 0) {
        cout << -1 << '\n';
        return;
    }
    
    vector<vector<int>> ans;
    for (int tm = 0; tm < 2 * n; tm++) {
        vector<int> s, tag(n);
        if (a == b) break;
        for (int i = 0; i < n; i++) {
            if (SZ(s) < n / 2 && a[i] < b[i]) {
                s.eb(i + 1);
                tag[i] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            if (SZ(s) < n / 2 && a[i] == b[i]) {
                s.eb(i + 1);
                tag[i] = 1;
            }
        }
        vector<pii> tmp;
        for (int i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                tmp.eb(a[i] - b[i], i);
            }
        }
        sort(ALL(tmp));
        for (auto [x, y] : tmp) {
            if (SZ(s) < n / 2) {
                s.eb(y + 1);
                tag[y] = 1;
            }
        }
        if (SZ(s) != (n / 2)) {
            cout << -1 << '\n';
            return;
        }
        ans.eb(s);
        for (int i = 0; i < n; i++) {
            if (tag[i]) a[i]++;
            else a[i]--;
        }
    }

    if (a != b) {
        cout << -1 << '\n';
        return;
    }
    cout << SZ(ans) << '\n';
    for (auto &v : ans) {
        for (int i : v) cout << i << ' ';
        cout << '\n';
    }
}

signed main() {
	IO;	
    int T = 1; 
    cin >> T;
	while (T--) solve();	
}
