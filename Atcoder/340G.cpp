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
#define mod 998244353
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

const int mxN = 2e5 + 5;

struct HLD {
    int n, tk;
    vector<int> sz, fa, bson, tp, dep, dfn;
    // hson -> big son
    // tp -> top of chain
    vector<vector<int>> g;
    void dfs(int u, int p) { 
        sz[u] = 1; fa[u] = p; bson[u] = -1;
        for (int v : g[u]) {
            if(v == p) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
            if(bson[u] == -1 || sz[v] > sz[bson[u]]) bson[u] = v;
        }
    }
    void link(int u, int p) {
        tp[u] = p; dfn[u] = ++tk;
        if(bson[u] != -1) link(bson[u], p);
        for(int v : g[u]) {
            if(v == fa[u] || v == bson[u]) continue;
            link(v, v);
        }
    }
    void jump(int a, int b) {
        int ans = 0;
        while(tp[a] != tp[b]) {
            if(dep[tp[a]] < dep[tp[b]]) swap(a, b);
            // do someting to [dfn[tp[a]], dfn[a]]
            a = fa[tp[a]];
        }
        if(dfn[a] > dfn[b]) swap(a, b);
        // don't forget [dfn[a], dfn[b]]
    }


    void init(int _n) {
        n = _n; tk = 0; tp.resize(n + 1);
        sz.resize(n + 1); fa.resize(n + 1); bson.resize(n + 1);
        dep.resize(n + 1); dfn.resize(n + 1); g.resize(n + 1);
    }
    void add_edge(int u, int v) {
        g[u].eb(v); g[v].eb(u);
    }
    void build() {
        for (int i = 1; i <= n; i++) {
            if (sz[i] == 0) { // haven't visitied yet
                dfs(i, -1);
                link(i, i);
            } 
        }
    }
    int lca(int a, int b) {
        while(tp[a] != tp[b]) {
            if(dep[tp[a]] < dep[tp[b]]) swap(a, b);
            a = fa[tp[a]];
        }
        return dep[a] < dep[b] ? a : b;
    }
} lca;

int n;
int a[mxN];
vector<int> G[mxN];
vector<int> seq[mxN];

int aimer;
int st[mxN], ed[mxN];
void dfs(int u, int p) {
    seq[a[u]].eb(u);
    st[u] = ++aimer;
    for (int v : G[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    ed[u] = aimer;
}

int ans = 0;
int dp[mxN], right_color[mxN];
vector<int> tr[mxN];

bool is_ancestor(int u, int v) {
    return st[u] <= st[v] && ed[v] <= ed[u];
}

void add_tree_edge(int u, int v) {
    tr[u].eb(v); tr[v].eb(u);
}

void cal_dp(int u, int p) {
    dp[u] = 1;
    int sub = 0;
    for (int v : tr[u]) {
        if (v == p) continue;
        cal_dp(v, u);
        sub = (sub + dp[v]) % mod;
        dp[u] = (dp[u] + dp[v] * dp[u] % mod) % mod;
    }
    dp[u] = (dp[u] - 1) % mod;
    if (right_color[u]) {
        dp[u] = (dp[u] + 1) % mod;
        ans = (ans + dp[u]) % mod;
    } else {
        ans = (ans + dp[u] - sub + mod) % mod;
    }
    right_color[u] = 0;
}

void build_vtree(int col) {
    vector<int> stk;
    vector<int> nw_seq;
    if (seq[col].empty()) return;
    if (SZ(seq[col]) == 1) {
        ans = (ans + 1) % mod;
        return;
    }
    if (SZ(seq[col]) == 2) {
        ans = (ans + 3) % mod;
        return;
    }

    int m = SZ(seq[col]);
    for (int i = 0; i < m; i++) {
        int u = seq[col][i];
        right_color[u] = 1;
        nw_seq.eb(u);
        if (i > 0) {
            int nw_node = lca.lca(u, seq[col][i-1]);
            nw_seq.eb(nw_node);
        }
    }

    sort(ALL(nw_seq), [](int a, int b) {
        return st[a] < st[b];
    });
    uni(nw_seq);

    for (int u : nw_seq) {
        if (stk.empty()) 
            stk.eb(u);
        else {
            while (!is_ancestor(stk.back(), u)) 
                stk.pop_back();
            add_tree_edge(stk.back(), u);
            stk.eb(u);
        }
    }

    int root = nw_seq[0];
    for (int u : nw_seq) {
        if (SZ(tr[u]) > 1)
            root = u;
    }

    // DP
    cal_dp(root, 0);

    // clear
    for (int u : nw_seq) {
        tr[u].clear();
    }
}

inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    lca.init(n);
    for (int i = 1; i < n; i++) {
        int u, v; 
        cin >> u >> v;
        G[u].eb(v); G[v].eb(u);
        lca.add_edge(u, v);
    }
    lca.build();

    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        build_vtree(i);
    }

    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
