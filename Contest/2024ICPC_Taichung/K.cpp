#include<bits/stdc++.h>
using namespace std;

#define SZ(x) (int)x.size()
#define ALL(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<ll, ll> pll;

const ll INF = (1LL<<60);

const int mxN = 2e5 + 5;

struct SCC { 
    int n, dft, nscc;
    vector<int> low, dfn, bln, instack, stk, sz;
    vector<vector<int>> G;
    void dfs(int u) {
        low[u] = dfn[u] = ++dft;
        instack[u] = 1, stk.pb(u);
        for (int v : G[u]) {
            if (!dfn[v])
                dfs(v), low[u] = min(low[u], low[v]);
            else if (instack[v] && dfn[v] < dfn[u])
                low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            for (; stk.back() != u; stk.pop_back()) {
                bln[stk.back()] = nscc;
                instack[stk.back()] = 0;
                sz[nscc]++;
            }
            sz[nscc]++;
            instack[u] = 0, bln[u] = nscc++, stk.pop_back();
        }
    }
    SCC(int _n): n(_n), dft(), nscc(), low(n), dfn(n), bln(n), instack(n), sz(n), G(n) {}
    int get_id(int u) { return bln[u]; }
    int get_sz(int u) { return sz[bln[u]]; }
    void add_edge(int u, int v) { G[u].eb(v); }
    void solve() {
        for (int i = 0; i < n; i++)
            if (!dfn[i]) dfs(i);
        low.clear(); dfn.clear();
        instack.clear();
    }
};

bitset<mxN> vis;
vector<int> G[mxN], rG[mxN];

vector<int> stk, rstk;
void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    stk.eb(u);
    for (int v : G[u]) {
        dfs(v);
    }
}

void rdfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    rstk.eb(u);
    for (int v : rG[u]) {
        rdfs(v);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    SCC scc(n);
    vector<pair<int, int>> edge;
    while (m--) {
        int u, v; cin >> u >> v;
        u--; v--;
        edge.eb(u, v);
        scc.add_edge(u, v);
    }
    scc.solve();

    vector<unordered_set<int>> st(n), rst(n);
    for (auto [u, v] : edge) {
        if (scc.get_id(u) == scc.get_id(v)) continue;
        st[scc.get_id(u)].insert(scc.get_id(v));
        rst[scc.get_id(v)].insert(scc.get_id(u));
    }
    edge.clear();

    int nsc = scc.nscc;
    for (int i = 0; i < nsc; i++) {
        for (int v : st[i]) G[i].eb(v);
        for (int v : rst[i]) rG[i].eb(v);
    }
    st.clear(); rst.clear();

    vector<int> ord(nsc);
    iota(ALL(ord), 0);

    std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    std::shuffle(ALL(ord), rnd);

    int mn = 2 * n;
    vector<int> del(nsc + 1);
    set<int> ans;
    for (int u : ord) {
        if (del[u]) continue;
        stk.clear(); rstk.clear();
        vis = 0; dfs(u);
        vis = 0; rdfs(u);

        int a = 0, b = 0;
        for (int i : stk) a += scc.sz[i];
        for (int i : rstk) b += scc.sz[i];

        int res = abs(a - b);
        if (res < mn) {
            mn = res;
            ans.clear();
            ans.insert(u);
        } else if (res == mn) {
            ans.insert(u);
        }

        if (a <= b) {
            for (int i : stk) del[i] = 1;
        } 
        if (b <= a) {
            for (int i : rstk) del[i] = 1;
        }
    }

    assert(SZ(ans) <= 16);
    for (int i = 0 ; i < n; i++) {
        if (ans.find(scc.get_id(i)) != ans.end()) cout << i + 1 << " ";
    }

}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}
