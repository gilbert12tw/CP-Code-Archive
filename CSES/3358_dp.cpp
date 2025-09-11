#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> G;
    vector<int> pairU, pairV, dist;
    const int INF = 1e9;

    HopcroftKarp(int _nL = 0, int _nR = 0) { init(_nL, _nR); }

    void init(int _nL, int _nR) {
        nL = _nL; nR = _nR;
        G.assign(nL + 1, vector<int>()); // 1-based
        pairU.assign(nL + 1, 0);
        pairV.assign(nR + 1, 0);
        dist.assign(nL + 1, 0);
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
    }

    // greedy pre-match to speed up early
    int greedy(int limit) {
        int matched = 0;
        for (int u = 1; u <= nL; ++u) {
            if (pairU[u] != 0) continue;
            for (int v : G[u]) {
                if (pairV[v] == 0) {
                    pairU[u] = v;
                    pairV[v] = u;
                    matched++;
                    break;
                }
            }
            if (matched >= limit) break;
        }
        return matched;
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= nL; ++u) {
            if (pairU[u] == 0) {
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
                if (pairV[v] == 0) {
                    reachable_free = true;
                } else if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
        return reachable_free;
    }

    bool dfs(int u) {
        for (int v : G[u]) {
            if (pairV[v] == 0 || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }

    int max_matching(int reach_limit = -1) {
        int matching = 0;
        if (reach_limit > 0) matching = greedy(reach_limit);
        else matching = greedy(INT_MAX);
        if (reach_limit != -1 && matching >= reach_limit) return matching;

        while (bfs()) {
            for (int u = 1; u <= nL; ++u) {
                if (pairU[u] == 0) {
                    if (dfs(u)) {
                        matching++;
                        if (reach_limit != -1 && matching >= reach_limit)
                            return matching;
                    }
                }
            }
        }
        return matching;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    HopcroftKarp hk(n, n);
    vector<vector<int>> G(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        hk.add_edge(a, b); // left a -> right b
        G[a].push_back(b); // for reconstruction convenience if needed
    }

    int need = n - 2; // matching >= n-2 => path cover size <=2
    int matching = hk.max_matching(need);
    if (matching < need) {
        cout << "NO\n";
        return 0;
    }

    vector<int> nxt(n + 1, 0), prev(n + 1, 0);
    for (int u = 1; u <= n; ++u) {
        if (hk.pairU[u] != 0) {
            int v = hk.pairU[u];
            nxt[u] = v;
            prev[v] = u;
        }
    }

    vector<vector<int>> paths;
    vector<char> visited(n + 1, 0);
    for (int u = 1; u <= n; ++u) {
        if (prev[u] == 0 && !visited[u]) {
            vector<int> path;
            int cur = u;
            while (cur != 0 && !visited[cur]) {
                path.push_back(cur);
                visited[cur] = 1;
                cur = nxt[cur];
            }
            paths.push_back(path);
        }
    }
    if (paths.size() > 2) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    for (int i = 0; i < 2; ++i) {
        if (i < (int)paths.size()) {
            cout << paths[i].size();
            for (int x : paths[i]) cout << ' ' << x;
            cout << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    return 0;
}

