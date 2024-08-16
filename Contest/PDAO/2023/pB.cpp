#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
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

const int mxN = 50000 + 5, mxM = 505;

int n, m, w[mxN], v[mxN];
int dp[mxN][mxM];
vector<int> g[mxN];

void dfs(int u) {
    if (SZ(g[u]) == 0) {
        dp[u][w[u]] = v[u];
        return;
    }
    for (int v : g[u]) {
        dfs(v);
        for (int i = 0; i <= m; i++) {
            dp[u][i] = max(dp[u][i], dp[v][i]);
        }
    }
    for (int i = m; i >= w[u]; i--) {
        dp[u][i] = max(dp[u][i], dp[u][i - w[u]] + v[u]);
    }
}

inline void solve() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> w[i] >> v[i] >> x;
        g[x].eb(i);
    }

    dfs(0);
    int ans = 0;
    for (int i = 0; i <= m; i++) ans = max(ans, dp[0][i]);
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
