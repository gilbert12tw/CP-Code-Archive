#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
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
#define inf 2000000000
#define INF 1000000000000000000
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline void solve() {
    int n, m, kk, s;
    cin >> n >> m >> kk >> s;
    vector<int> a(n), b(n);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;

    vector<int> t(m), c(m);
    vector<int> id_a, id_b;
    for (int i = 0; i < m; i++) {
        cin >> t[i] >> c[i];
        if (t[i] == 1) id_a.eb(i);
        if (t[i] == 2) id_b.eb(i);
    }

    sort(ALL(id_a), [&](int x, int y) {
        return c[x] < c[y];
    });
    sort(ALL(id_b), [&](int x, int y) {
        return c[x] < c[y];
    });

    vector<pii> item;
    auto check = [&](int mid) -> bool {
        int mn_a = inf, mn_b = inf, mn_ida = -1, mn_idb = -1;
        int budget = s;
        for (int i = 0; i <= mid; i++) {
            if (mn_ida == -1 || a[mn_ida] > a[i]) mn_ida = i;
            if (mn_idb == -1 || b[mn_idb] > b[i]) mn_idb = i;
            ckmin(mn_a, a[i]);
            ckmin(mn_b, b[i]);
        }
        vector<int> bought(m);
        int j = 0, k = 0, cnt = 0;
        item.clear();

        while (cnt < kk) {
            if (k == SZ(id_b) || (j < SZ(id_a) && c[id_a[j]] * mn_a <= c[id_b[k]] * mn_b)) {
                budget -= c[id_a[j]] * mn_a;
                if (budget < 0) return false;
                item.eb(id_a[j], mn_ida);
                bought[id_a[j++]] = 1;
                cnt++;
            }
            else if (j == SZ(id_a) || (k < SZ(id_b) && c[id_b[k]] * mn_b <= c[id_a[j]] * mn_a)) {
                budget -= c[id_b[k]] * mn_b;
                if (budget < 0) return false;
                item.eb(id_b[k], mn_idb);
                bought[id_b[k++]] = 1;
                cnt++;
            } else {
                return false;
            }
        }
        return true;
    };

    int l = 0, r = n - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    check(l);
    if (SZ(item) != kk) {
        cout << -1 << '\n';
        return;
    }
    cout << l + 1 << '\n';
    for (auto [x, y] : item) cout << x+1 << ' ' << y+1 << '\n';
}

signed main() {
	IO;	
	solve();	
}
