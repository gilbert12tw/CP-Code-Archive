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
 
const int mxN = 1e5 + 5, mxM = 2e5 + 5;
 
int n, m, eu[mxM], ev[mxM];
bitset<mxM> vis, bridge;
vector<int> g[mxN];
 
int dfn[mxN], low[mxN], aimer;
int ans = 0;
void dfs(int u) {
	low[u] = dfn[u] = ++aimer;
	for (int i : g[u]) {
		int v = eu[i] ^ ev[i] ^ u;
		if (vis[i]) continue;
		vis[i] = 1;
		if (!dfn[v]) { 
			dfs(v);
            if (low[v] > dfn[u]) bridge[i] = 1;
			low[u] = min(low[u], low[v]);
		}
		low[u] = min(low[u], dfn[v]);
	}
}
 
inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        g[eu[i]].eb(i);
        g[ev[i]].eb(i);
    }
 
    for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i);
 
    cout << bridge.count() << '\n';
    for (int i = 0; i < m; i++) if (bridge[i]) {
        cout << eu[i] << ' ' << ev[i] << '\n';
    }
}
 
signed main() {
	IO;	
	solve();	
}

