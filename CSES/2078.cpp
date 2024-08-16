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

int n, m;
int eu[mxN], ev[mxN];
vector<int> g[mxN];
bitset<mxN> vis, in;

int ans = 0;
void dfs(int u) {
    in[u] = 1;
    for (int e : g[u]) {
        if (vis[e]) continue;
        vis[e] = 1;
        int v = eu[e] ^ ev[e] ^ u;
        if (in[v]) {
            ans++;
            continue;
        }
        dfs(v);
    }
    in[u] = 0;
}

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        g[eu[i]].eb(i);
        g[ev[i]].eb(i);
    }
    for (int i = 1; i <= n; i++) dfs(i);
    int res = 1;
    while (ans--) res = res * 2 % mod;
    cout << res << '\n';
}

signed main() {
	IO;	
	solve();	
}
