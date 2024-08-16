#include<bits/stdc++.h>
//#define loli
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

const int mxN = 1e5 + 5;
vector<int> g[mxN];
bitset<mxN> chosed;

// LCA binary jump
int up[mxN][25], dep[mxN];
const int mxL = 20;

void dfs(int u, int p, vector<int> &dfn) {
	if (p != -1) up[u][0] = p;
    if (chosed[u]) dfn.eb(u);

	for (int i = 1; (1<<i) <= dep[u]; i++) {
		up[u][i] = up[up[u][i-1]][i-1];
	}

	for (int v : g[u]) {
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u, dfn);
	}
}

inline int lca(int u, int v) {
	if (u == v) return u;
	if (dep[u] < dep[v]) swap(u, v);

	for (int i = mxL; i >= 0; i--) {
		if (up[u][i] and dep[up[u][i]] >= dep[v]) {
			u = up[u][i];
		}
	}

	if (u == v) return u;

	for (int i = mxL; i >= 0; i--) {
		if (up[u][i] and up[v][i] and up[u][i] != up[v][i]) {
			u = up[u][i];
			v = up[v][i];
		}
	}

	return up[u][0];
}

int dis(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}

inline void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        //g[u].eb(v, w);
        //g[v].eb(u, w);
        g[u].eb(v);
        g[v].eb(u);
    }

    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        chosed[x] = 1;
    }
    vector<int> dfn;
    dfs(1, -1, dfn);
    int ans = 0;
    for (int i = 1; i < SZ(dfn); i++) {
        test(dfn[i]);
        ans += dis(dfn[i], dfn[i-1]);
    }
    ans += dis(dfn.back(), dfn[0]);
    cout << (ans / 2) + 1 << '\n';
}

signed main() {
	IO;	
	solve();	
}
