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
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 1e5 + 5;
vector<int> G[mxN];
int pa[mxN], dep[mxN];

void dfs(int u, int p = -1) {
    pa[u] = p;
    for (int v : G[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

inline void solve() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].eb(v); G[v].eb(u);
    }
    dep[1] = 0;
    dfs(1);

    vector<int> edge_mask(n + 1);
    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        while (a != b) {
            if (dep[a] < dep[b]) swap(a, b);
            edge_mask[a] |= (1<<i);
            a = pa[a];
        }
    }

    set<int> msk;
    for (int i = 1; i <= n; i++) {
        msk.insert(edge_mask[i]);
    }

    vector<int> dp((1<<k) + 10, inf);
    dp[0] = 0;
    for (int b : msk) {
        for (int i = 0; i < (1<<k); i++) {
            ckmin(dp[i | b], dp[i] + 1);
        }
    }
    cout << dp[(1<<k)-1] << '\n';

    // clear
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
