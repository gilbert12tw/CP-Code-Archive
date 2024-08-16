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


const int mxN = 1e5 + 5;
int n;
int c[mxN];


// LCA binary jump
int up[mxN][25], dep[mxN];
const int mxL = 20;
vector<int> g[mxN];

int dfn[mxN], pos[mxN], tot;

void dfs(int u, int p = -1) {
	if (p != -1) up[u][0] = p;
    dfn[u] = ++tot;
    pos[tot] = u;

	for (int i = 1; (1<<i) <= dep[u]; i++) {
		up[u][i] = up[up[u][i-1]][i-1];
	}

	for (int v : g[u]) {
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

int dis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

set<int> st[mxN];
int cost[mxN];

void insert(int x, int color) {
    if (st[color].empty()) {
        st[color].insert(dfn[x]);
    } else {
        auto it = st[color].insert(dfn[x]).F;
        if (it != st[color].begin() && next(it) != st[color].end()) {
            cost[color] -= dis(pos[*prev(it)], pos[*next(it)]);
        } 
        if (it != st[color].begin()) {
            cost[color] += dis(pos[*prev(it)], pos[*it]);
        }
        if (next(it) != st[color].end()) {
            cost[color] += dis(pos[*next(it)], pos[*it]);
        }
    }
}

void del(int x, int color) {
    assert(st[color].size() > 0);
    if (st[color].size() == 1) {
        st[color].erase(dfn[x]);
    } else {
        auto it = st[color].lower_bound(dfn[x]);
        if (it != st[color].begin() && next(it) != st[color].end()) {
            cost[color] += dis(pos[*prev(it)], pos[*next(it)]);
        } 
        if (it != st[color].begin()) {
            cost[color] -= dis(pos[*prev(it)], pos[*it]);
        }
        if (next(it) != st[color].end()) {
            cost[color] -= dis(pos[*next(it)], pos[*it]);
        }
        st[color].erase(it);
    }
}

int cal(int color) {
    if (SZ(st[color]) == 0) return -1;
    if (SZ(st[color]) == 1) return 0;
    return (cost[color] + dis(pos[*st[color].begin()], pos[*prev(st[color].end())])) / 2;
}


inline void solve() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        insert(i, c[i]);
    }
    int q; cin >> q;
    while (q--) {
        char o; int x, y;
        cin >> o;
        if (o == 'Q') {
            cin >> x;
            cout << cal(x) << '\n';
        } else {
            cin >> x >> y;
            del(x, c[x]);
            c[x] = y;
            insert(x, c[x]);
        }
    }
}

signed main() {
	IO;	
	solve();	
}
