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

struct Group {
    vector<pii> raw;
    vector<int> p_cnt, p_val;
    int total_cnt = 0;

    void add(int v, int k) {
        raw.eb(v, k);
    }

    void build(int limit) {
        sort(ALL(raw), [](const pii& a, const pii& b) {
            return a.f > b.f;
        });

        p_cnt.pb(0);
        p_val.pb(0);

        for (auto& p : raw) {
            if (total_cnt >= limit) break; 
            int take = min(p.s, limit - total_cnt);

            total_cnt += take;
            p_cnt.pb(total_cnt);
            p_val.pb(p_val.back() + take * p.f);
        }
    }

    int query(int k) {
        if (k <= 0) return 0;
        if (k >= total_cnt) return p_val.back();

        auto it = lb(p_cnt, k);
        int idx = it - p_cnt.begin(); // index in p_cnt

        int prev_c = p_cnt[idx - 1];
        int prev_v = p_val[idx - 1];

        int unit_val = raw[idx - 1].f;

        return prev_v + (k - prev_c) * unit_val;
    }
} G[4]; // G[1], G[2], G[3]

inline void solve() {
    int n, c;
    cin >> n >> c;

    for (int i = 0; i < n; i++) {
        int w, v, k;
        cin >> w >> v >> k;
        G[w].add(v, k);
    }

    for (int i = 1; i <= 3; i++) G[i].build(c + 5);

    auto calc_val = [&](int z, int y) -> int {
        int rem_w = c - 3 * z - 2 * y;
        if (rem_w < 0) return -INF;
        return G[3].query(z) + G[2].query(y) + G[1].query(rem_w);
    };

    auto solve_inner = [&](int z) -> int {
        int rem_for_2 = c - 3 * z;
        if (rem_for_2 < 0) return -INF;

        int max_y = min(G[2].total_cnt, rem_for_2 / 2);
        int l = 0, r = max_y;

        while (r - l > 100) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;
            if (calc_val(z, m1) < calc_val(z, m2)) l = m1;
            else r = m2;
        }

        int ret = -INF;
        for (int i = l; i <= r; i++) ckmax(ret, calc_val(z, i));
        return ret;
    };

    int max_z = min(G[3].total_cnt, c / 3);
    int l = 0, r = max_z;

    while (r - l > 100) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (solve_inner(m1) < solve_inner(m2)) l = m1;
        else r = m2;
    }

    int ans = 0;
    for (int i = l; i <= r; i++) ckmax(ans, solve_inner(i));

    cout << ans << '\n';
}

signed main() {
    IO;
    solve();
}
