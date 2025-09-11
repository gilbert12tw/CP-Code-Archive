#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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

const int N = 2e5 + 5;
/*
struct Bipartite_Matching { // 0-base
    int mp[N], mq[N], dis[N + 1], cur[N], l, r;
    vector<int> G[N + 1];
    bool dfs(int u) {
        for (int &i = cur[u]; i < SZ(G[u]); ++i) {
            int e = G[u][i];
            if (mq[e] == l ||
                (dis[mq[e]] == dis[u] + 1 && dfs(mq[e])))
                return mp[mq[e] = u] = e, 1;
        }
        return dis[u] = -1, 0;
    }
    bool bfs() {
        queue<int> q;
        fill_n(dis, l + 1, -1);
        for (int i = 0; i < l; ++i)
            if (!~mp[i]) q.push(i), dis[i] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int e : G[u]) if (!~dis[mq[e]])
                q.push(mq[e]), dis[mq[e]] = dis[u] + 1;
        }
        return dis[l] != -1;
    }
    int matching() {
        int res = 0;
        fill_n(mp, l, -1), fill_n(mq, r, l);
        while (bfs()) {
            fill_n(cur, l, 0);
            for (int i = 0; i < l; ++i)
                res += (!~mp[i] && dfs(i));
        }
        return res; // (i, mp[i] != -1)
    }
    void add_edge(int s, int t) { G[s].pb(t); }
    void init(int _l, int _r) {
        l = _l, r = _r;
        for (int i = 0; i <= l; ++i) G[i].clear();
    }
} bp;
*/

struct HopcroftKarp {
    int nL, nR; // left size, right size (0-based, [0..nL), [0..nR))
    vector<vector<int>> G;
    vector<int> pairU, pairV, dist;
    const int INF = 1e9;

    HopcroftKarp(int _nL = 0, int _nR = 0) { init(_nL, _nR); }

    void init(int _nL, int _nR) {
        nL = _nL; nR = _nR;
        G.assign(nL, vector<int>());
        pairU.assign(nL, -1);
        pairV.assign(nR, -1);
        dist.assign(nL, 0);
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
    }

    // greedy pre-matching to speed up
    int greedy_match(int limit = INT_MAX) {
        int match = 0;
        for (int u = 0; u < nL; ++u) {
            if (pairU[u] != -1) continue;
            for (int v : G[u]) {
                if (pairV[v] == -1) {
                    pairU[u] = v;
                    pairV[v] = u;
                    match++;
                    break;
                }
            }
            if (match >= limit) return match;
        }
        return match;
    }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nL; ++u) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        bool reachable_free = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : G[u]) {
                if (pairV[v] != -1 && dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
                if (pairV[v] == -1) {
                    reachable_free = true;
                }
            }
        }
        return reachable_free;
    }

    bool dfs(int u) {
        for (int v : G[u]) {
            if (pairV[v] == -1 || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }
    int max_matching(int reach_limit = INT_MAX) {
        int matching = greedy_match(reach_limit);
        if (matching >= reach_limit) return matching;

        while (bfs()) {
            for (int u = 0; u < nL; ++u) {
                if (pairU[u] == -1) {
                    if (dfs(u)) {
                        matching++;
                        if (matching >= reach_limit) return matching;
                    }
                }
            }
        }
        return matching;
    }
} bp;


vector<int> G[N];
int vis[N];
void dfs(int u, int cnt, vector<int> &stk) {
    vis[u] = cnt; stk.eb(u);
    for (int v : G[u]) {
        if (!vis[v]) dfs(v, cnt, stk);
    }
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    HopcroftKarp bp(n, n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        bp.add_edge(u, v);
    }
    int sp_path = n - bp.max_matching();
    if (sp_path > 2) {
        cout << "NO\n";
        return;
    }

    vector<int> indeg(n);
    for (int i = 0; i < n; i++) {
        int v = bp.pairU[i];
        if (v == -1) continue;
        G[i].eb(v);
        indeg[v]++;
    }

    cout << "YES\n";
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0 && !vis[i]) {
            vector<int> stk;
            dfs(i, ++cnt, stk);
            cout << SZ(stk) << ' ';
            for (int j : stk) cout << j + 1 << ' ';
            cout << '\n';
        }
    }
}

signed main() {
	IO;	
	solve();	
}
