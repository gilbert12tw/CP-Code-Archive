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
#define inf 1000000000
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
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> G(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].eb(y, z);
        G[y].eb(x, z);
    }

    vector<int> vis(n + 1), sum(n + 1);
    bool ok = 1;
    vector<int> stk, id;
    auto dfs = [&](int u, auto &&dfs) -> void {
        vis[u] = 1;
        stk.eb(sum[u]);
        id.eb(u);
        for (auto [v, w] : G[u]) {
            if (vis[v]) {
                if (sum[v] != (sum[u] ^ w)) ok = 0;
                continue;
            }
            sum[v] = sum[u] ^ w;
            dfs(v, dfs);
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            stk.clear();
            id.clear();
            dfs(i, dfs);

            int tot = SZ(stk);
            vector<int> cnt(35);
            int ans = 0;
            for (int j = 32; j >= 0; j--) {
                int cnt = 0;
                for (int i : stk) cnt += (get_bit(i, j));
                if (cnt > tot - cnt) {
                    ans |= (1<<j);
                }
            }
            for (int u : id) sum[u] ^= ans;
        }
    }
    if (!ok) {
        cout << -1 << '\n';
        return;
    }
    for (int i = 1; i <= n; i++) cout << sum[i] << ' ';
}

signed main() {
	IO;	
	solve();	
}
