#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
//#pragma loop-opt(on)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
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

struct DSU {
	vector<int> dsu, sz;
	void init(int n) {
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
		if(sz[a] > sz[b]) swap(a, b);
		dsu[a] = b;
		sz[b] += sz[a];
	}
};

const int mxN = 1005, mxM = 1000005;
vector<int> g[mxN];
bitset<mxM> vis;
int mat[mxN][mxN];
int eu[mxM], ev[mxM];
int del[mxM];
int dfn[mxN], low[mxN], aimer;
vector<int> bedge;
void dfs(int u) {
	low[u] = dfn[u] = ++aimer;
	for (int i : g[u]) {
        if (del[i]) continue;
		int v = eu[i] ^ ev[i] ^ u;
		if (vis[i]) continue;
		vis[i] = 1;
		if (!dfn[v]) { 
			dfs(v);
            if (low[v] > dfn[u]) {
                bedge.eb(i);
            }
			low[u] = min(low[u], low[v]);
		}
		low[u] = min(low[u], dfn[v]);
	}
}

void find_bridge(int n) {
    vis = 0;
    bedge.clear();
    aimer = 0;
    for (int i = 1; i <= n; i++) dfn[i] = low[i] = 0;
    for (int i = 1; i <= n; i++) {
        if (dfn[i]) continue;
        dfs(i);
    }
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu[3];
    for (int i = 0; i < 3; i++) dsu[i].init(n);
    int ecnt = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        mat[u][v] = mat[v][u] = 1;
        for (int j = 0; j < 3; j++) {
            if (dsu[j].get(u) == dsu[j].get(v)) continue;
            dsu[j].oni(u, v);
            eu[ecnt] = u; ev[ecnt++] = v;
            g[u].eb(ecnt - 1); g[v].eb(ecnt - 1);
            break;
        }
    }
    
    set<vector<int>> tri;
    for (int i = 0; i < ecnt; i++) {
        del[i] = 1;
        find_bridge(n);
        int u = eu[i], v = ev[i];
        test(u, v);
        for (int e : bedge) {
            int uu = eu[e], vv = ev[e];
            test(uu, vv);
            if (uu == u && mat[v][vv]) {
                vi tmp = {u, v, vv};
                sort(ALL(tmp));
                tri.insert(tmp);
            }
            if (uu == v && mat[u][vv]) {
                vi tmp = {u, v, vv};
                sort(ALL(tmp));
                tri.insert(tmp);
            }
            if (vv == u && mat[v][uu]) {
                vi tmp = {u, v, uu};
                sort(ALL(tmp));
                tri.insert(tmp);
            }
            if (vv == v && mat[u][uu]) {
                vi tmp = {u, v, uu};
                sort(ALL(tmp));
                tri.insert(tmp);
            }
        }
        del[i] = 0;
    }
    cout << SZ(tri) << '\n';
    for (auto v : tri) {
        test(v[0], v[1], v[2]);
    }
    test(ecnt);
}

signed main() {
	IO;	
	solve();	
}
