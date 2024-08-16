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

int pw[mxN], n, m;
vector<int> tr[mxN];

int build_kruskal(vector<array<int, 3>> &edge) {
    sort(ALL(edge), [](auto a, auto b) {
        return a[2] > b[2];
    });
    int id_cnt = n + 1;
    DSU dsu(2 * n + 1);
    
    for (auto a : edge) {
        int u = dsu.get(a[0]);
        int v = dsu.get(a[1]);
        if (u == v) continue;
        dsu.oni(u, id_cnt);
        dsu.oni(v, id_cnt);
        tr[id_cnt].eb(u);
        tr[id_cnt].eb(v);
        pw[id_cnt] = a[2];
        id_cnt++;
    }
    return id_cnt - 1;
}

// LCA binary jump
int up[mxN][21], dep[mxN];
int dis[mxN];
const int mxL = 20;

void dfs(int u, int p = -1) {
	if (p != -1) up[u][0] = p;

	for (int i = 1; (1<<i) <= dep[u]; i++) 
		up[u][i] = up[up[u][i-1]][i-1];

	for (int v : tr[u]) {
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
        dis[u] = min(dis[u], dis[v]);
	}
}


vector<pii> g[mxN];

void dijkstra() {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(0, 1);
    dis[1] = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (dis[u] < d) continue;
        for (auto [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push(dis[v], v);
            }
        }
    }
}

int jump(int x, int l) {
    for (int i = mxL; i >= 0; i--) {
        if (pw[up[x][i]] > l) {
            x = up[x][i];
        }
    }
    return dis[x];
}

void init() {
    for (int i = 1; i <= 2 * n; i++) {
        g[i].clear();
        dis[i] = inf;
        pw[i] = 0;
        for (int j = 0; j <= 20; j++) up[i][j] = 0;
        tr[i].clear();
    }
}

inline void solve() {
    cin >> n >> m;
    init();

    vector<array<int, 3>> edge(m);
    for (int i = 0; i < m; i++) {
        int u, v, l, a;
        cin >> u >> v >> l >> a;
        edge[i][0] = u;
        edge[i][1] = v;
        edge[i][2] = a;
        g[u].eb(v, l);
        g[v].eb(u, l);
    }

    dijkstra();
    int root = build_kruskal(edge);
    dep[root] = 0;
    dfs(root);

    int q, k, s, lastans = 0;
    cin >> q >> k >> s;
    for (int i = 0; i < q; i++) {
        int v, p; cin >> v >> p;
        v = (v + k * lastans - 1) % n + 1;
        p = (p + k * lastans) % (s + 1);
        lastans = jump(v, p);
        cout << lastans << '\n';            
    }
}

signed main() {
	IO;	
    int T; cin >> T; 
	while (T--) solve();	
}
