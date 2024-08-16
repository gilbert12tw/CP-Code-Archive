#include<bits/stdc++.h>
#define loli
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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

// LCA binary jump
const int mxN = 1e5 + 5;
int up[mxN][25], dep[mxN];
const int mxL = 22;

vector<pii> g[mxN];
int delu, delv, delw;
int vis[mxN];
int dis[mxN];

void dfs(int u, int p = -1) {
	if (p != -1) up[u][0] = p;

	for (int i = 1; (1<<i) <= dep[u]; i++) {
		if (up[u][i-1] != -1) 
            up[u][i] = up[up[u][i-1]][i-1];
	}
    vis[u] = 1;

	for (auto [v, w] : g[u]) {
		if (v == p) continue;
        if (vis[v]) {
            if (delu != 0) continue;
            delu = u; delv = v; delw = w;
            continue;
        }
		dep[v] = dep[u] + 1;
        dis[v] = dis[u] + w;
		dfs(v, u);
	}
}

inline int lca(int u, int v) {
	if (u == v) return u;
	if (dep[u] < dep[v]) swap(u, v);

	for (int i = mxL; i >= 0; i--) {
		if (up[u][i] != -1 and dep[up[u][i]] >= dep[v]) {
			u = up[u][i];
		}
	}

	if (u == v) return u;

	for (int i = mxL; i >= 0; i--) {
		if (up[u][i] != - 1 and up[v][i] != -1 and up[u][i] != up[v][i]) {
			u = up[u][i];
			v = up[v][i];
		}
	}

	return up[u][0];
}

inline int dist(int u, int v) {
    return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}


inline void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        vis[i] = 0;
        dep[i] = 0;
        dis[i] = 0;
        for (int j = 0; j <= mxL; j++) up[i][j] = -1;
    }
    delu = delv = delw = 0;

    for (int i = 0; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].eb(v, w);
        g[v].eb(u, w);
    }

    dfs(1);
    //test(delw);

    while (q--) {
        int a, b;
        cin >> a >> b;
        int ans = min(dist(a, b), 
                min(dist(a, delu) + dist(b, delv), dist(a, delv) + dist(b, delu)) + delw);
        cout << ans << '\n';
    }

}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
