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

//Block Cut Tree
const int mxM = 1e6, mxN = 1e6; // N double size
int n, m, q, k, eu[mxM], ev[mxM];
bitset<mxM> vis;
vector<int> g[mxN], tr[mxN];

int dfn[mxN], low[mxN], aimer, bcnt;
vector<int> stk;

void Tarjan(int u, int rt) {
	low[u] = dfn[u] = ++aimer;
    stk.eb(u);
	for (int i : g[u]) {
		int v = eu[i] ^ ev[i] ^ u;
		if (vis[i]) continue;
		vis[i] = 1;
		if (!dfn[v]) { 
			Tarjan(v, rt);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) { 
                ++bcnt; 
                int x = stk.back();
                test(bcnt);
                do {
                    x = stk.back(); stk.pop_back();
                    test(x);
                    tr[bcnt + n].eb(x);
                    tr[x].eb(bcnt + n);
                } while (x != v);
                // add a node bcnt + n
                test(u);
                tr[bcnt + n].eb(u);
                tr[u].eb(bcnt + n);
            }
		}
		low[u] = min(low[u], dfn[v]);
	}
}

void build_BCT() {
    for (int i = 1; i <= n; i++) if (!dfn[i]) {
        stk.clear();
        Tarjan(i, i);
    }
}

// heavy light decomposition
int sz[mxN], bson[mxN];

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : tr[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[bson[u]] < sz[v]) bson[u] = v;
    }
}

// int dfn[mxN], aimer
int tp[mxN], dep[mxN], pa[mxN];
void link(int u, int p, int tp_node, int deep) {
    dfn[u] = ++aimer;
    tp[u] = tp_node;
    pa[u] = p;
    dep[u] = deep;
    if (bson[u]) link(bson[u], u, tp_node, deep + 1);
    for (int v : tr[u]) {
        if (v == bson[u] || v == p) continue;
        link(v, u, v, deep + 1);
    }
}

void build_HLD() {
    aimer = 0;
    for (int i = 1; i <= n; i++) if (!sz[i]) {
        dfs(i, 0);
        link(i, 0, i, 1);
    }
}

int check(int a, int b, int c) {
    test(dfn[c]);
    while (tp[a] != tp[b]) {
        if (dep[tp[a]] < dep[tp[b]]) swap(a, b);
        test(tp[a], a, dfn[tp[a]], dfn[a], tp[b], dep[tp[b]], dep[tp[a]]);
        if (dfn[tp[a]] <= dfn[c] && dfn[c] <= dfn[a]) return 0; 
        a = pa[tp[a]];
    }
    test(dfn[a], dfn[b]);
    if (min(dfn[a], dfn[b]) <= dfn[c] && dfn[c] <= max(dfn[a], dfn[b])) return 0;
    return 1;
}

inline void solve() {
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        g[eu[i]].eb(i);
        g[ev[i]].eb(i);
    }
    build_BCT();
    build_HLD();

    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (check(a, b, c)) cout << "YES\n";
        else cout << "NO\n";
    }
}

signed main() {
	IO;	
	solve();	
}
