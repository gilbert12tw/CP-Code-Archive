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
		if(sz[a] > sz[b]) swap(a, b);
		dsu[a] = b;
		sz[b] += sz[a];
	}
};

const int mxN = 1005, mxM = 10000005;
vector<int> g[mxN];
bitset<mxN> vis;
int eu[mxM], ev[mxM];
int del[mxM];

void dfs_check(int u) {
    vis[u] = 1;
    for (int e : g[u]) {
        if (del[e]) continue;
        int v = eu[e] ^ ev[e] ^ u;
        if (vis[v]) continue;
        dfs_check(v);
    }
}

int check(int n) {
    vis = 0;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        dfs_check(i);
        res++;
    }
    return res;
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    bitset<100> mat[100]; 
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        mat[u][v] = mat[v][u] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            ans += (mat[i] & mat[j]).count();
        }
    }
    cout << ans << '\n';
}

signed main() {
    solve();
}
