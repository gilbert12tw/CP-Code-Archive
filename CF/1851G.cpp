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
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 4e5 + 5;

int n, m;
int h[mxN];

struct DSU {
	vector<int> dsu, sz;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
	void oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return;
		dsu[a] = b;
		sz[b] += sz[a];
	}
};

int up[mxN][21], dep[mxN];
const int mxL = 20;
vector<int> tr[mxN];

int build_kruskal(vector<array<int, 3>> &edge, int n) {
    sort(ALL(edge), [](auto a, auto b) {
        return a[2] < b[2];
    });
    int id_cnt = n + 1;

    DSU dsu(2 * n + 1);
    for (int i = 0; i <= 2 * n + 1; i++) { 
        tr[i].clear();
        dep[i] = 0;
        for (int j = 0; j <= 20; j++) up[i][j] = 0;
    }

    for (auto a : edge) {
        int u = dsu.get(a[0]);
        int v = dsu.get(a[1]);
        if (u == v) continue;
        dsu.oni(u, id_cnt);
        dsu.oni(v, id_cnt);
        tr[id_cnt].eb(u);
        tr[id_cnt].eb(v);
        h[id_cnt] = a[2];
        id_cnt++;
    }
    return id_cnt - 1;
}

// LCA binary jump

void dfs(int u, int p = -1) {
	if (p != -1) up[u][0] = p;

	for (int i = 1; (1<<i) <= dep[u]; i++)
		up[u][i] = up[up[u][i-1]][i-1];

	for (int v : tr[u]) {
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
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

inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        cin >> h[i];
    vector<array<int, 3>> edge;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        edge.pb({u, v, max(h[u], h[v])});
    }
    for (int i = 2; i <= n; i++) {
        edge.pb({1, i, INF});
    }
    int root = build_kruskal(edge, n);
    dfs(root);

    int q; 
    cin >> q;
    while (q--) {
        int a, b, e;
        cin >> a >> b >> e;
        if (h[lca(a, b)] - h[a] <= e) cout << "yes\n";
        else cout << "no\n";
    }
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
