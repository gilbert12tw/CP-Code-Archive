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

const int mxN = 2e6 + 5;

vector<int> g[mxN];
int pa[mxN], sz[mxN];
bitset<mxN> del;
void get_sz(int u, int p) {
	sz[u] = 1;
	for (int v : g[u]) {
		if (v == p or del[v]) continue;
		get_sz(v, u);
		sz[u] += sz[v];	
	}
}

int get_centroid(int u, int n, int p) {
	for (int v : g[u]) {
		if (v != p and !del[v] and sz[v] * 2 > n) 
			return get_centroid(v, n, u);
	}
	return u;
}

int build(int u) {
	get_sz(u, -1);	
	int centroid = get_centroid(u, sz[u], -1);
	del[centroid] = 1;
	for (int v : g[centroid]) {
		if (del[v]) continue;
		pa[build(v)] = centroid;
	}
	return centroid;
}


inline void solve() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
        pa[i] = -1;
    }
    build(1);
    for (int i = 1; i <= n; i++) cout << pa[i] << ' ';
}

signed main() {
	IO;	
	solve();	
}
