#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define eb emplace_back
#define ALL(a) a.begin(), a.end()
#define SZ(a) ((int)a.size())
#define mod 998244353

#ifdef debug
template <typename T>
ostream& operator << (ostream &o, vector<T> vec) {
    o << "{"; int f = 0; for (T i : vec) o << (f++ ? " " : "") << i; return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m"; (..., (cerr << a << " ")); cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#endif

class BCC {
    int n, ecnt, bcnt;
    vector<vector<pair<int, int>>> g;
    vector<int> dfn, low, bcc, stk;
    vector<bool> ap, bridge;
    void dfs(int u, int f) {
        dfn[u] = low[u] = dfn[f] + 1;
        int ch = 0;
        for (auto [v, t] : g[u]) if (bcc[t] == -1) {
            bcc[t] = 0; stk.push_back(t);
            if (dfn[v]) {
                low[u] = min(low[u], dfn[v]);
                continue;
            }
            ++ch, dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) bridge[t] = true;
            if (low[v] < dfn[u]) continue;
            ap[u] = true;
            while (not stk.empty()) {
                int o = stk.back(); stk.pop_back();
                bcc[o] = bcnt;
                if (o == t) break;
            }
            bcnt += 1;
        }
        ap[u] = ap[u] and (ch != 1 or u != f);
    }

    public:
    BCC(int n_) : n(n_), ecnt(0), bcnt(0), g(n), dfn(n), low(n), stk(), ap(n) {}
    void add_edge(int u, int v) {
        g[u].emplace_back(v, ecnt);
        g[v].emplace_back(u, ecnt++);
    }
    void solve() {
        bridge.assign(ecnt, false);
        bcc.assign(ecnt, -1);
        for (int i = 0; i < n; ++i)
            if (not dfn[i]) dfs(i, i);
    }
    int bcc_id(int x) const { return bcc[x]; }
    bool is_ap(int x) const { return ap[x]; }
    bool is_bridge(int x) const { return bridge[x]; }
};

void solve() {
    int n, m, V;
    cin >> n >> m >> V;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) 
        cin >> a[i];

    BCC bcc(n + 1);
    vector<pii> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        bcc.add_edge(u, v);
        edges.eb(u, v);
    }
    bcc.solve();

    vector<vector<int>> G(n + 1);
    for (int i = 0; i < m; i++) {
        if (bcc.is_bridge(i))
            continue;
        int u = edges[i].first, v = edges[i].second;
        //bug(u, v);
        G[u].eb(v);
        G[v].eb(u);
    }

    vector<int> vis(n + 1), col(n + 1);
    map<int, int> mp;

    auto dfs = [&](int u, int &ok, auto&& dfs) -> void {
        mp[a[u]]++;
        vis[u] = 1;
        for (int v : G[u]) {
            if (vis[v] && col[v] == col[u]) ok = 0;
            if (vis[v]) continue;
            col[v] = col[u] ^ 1;
            dfs(v, ok, dfs);
        }
    };

    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        int ok = 1;
        mp.clear();
        dfs(i, ok, dfs);
        //bug(ok);
        if (SZ(mp) == 1) {
            if (mp.begin()->first == -1) {
                if (ok) ans = ans * V % mod;
                // else nothing
            } else if (mp.begin()->first != 0) {
                if (!ok) ans = 0;
            }
        } else if (SZ(mp) == 2) {
            if (mp.begin()->first == -1) {
                if (!ok && mp.find(0) == mp.end()) ans = 0;
            } else {
                ans = 0;
            }
        } else {
            ans = 0;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
