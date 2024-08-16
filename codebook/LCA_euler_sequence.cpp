// LCA euler sequence
struct LCA_euler {
    int pos[mxN], dep[mxN], tp;
    vector<int> g[mxN];
    pii st[mxN * 2][22];

    void euler_dfs(int u, int p) {
        test(u);
        pos[u] = tp;
        st[tp++][0] = mkp(dep[u], u);
        for (int v : g[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            euler_dfs(v, u);
            st[tp++][0] = mkp(dep[u], u);
        }
    }

    inline int query(int l, int r) {
        int k = __lg(r - l + 1);
        pii tmp = min(st[l][k], st[r - (1<<k) + 1][k]);
        return tmp.first;
    }

    // public
    inline void build() {
        euler_dfs(1, -1);
        for(int i = 0; (1<<i) < tp; i++) {
            for(int j = 0; j + (1<<i) - 1 < tp; j++) {
                st[j][i + 1] = min(st[j][i], st[j + (1<<i)][i]);
            }
        }
    }

    inline int dis(int u, int v) {
        if (pos[u] > pos[v]) swap(u, v);
        return dep[u] + dep[v] - 2 * query(pos[u], pos[v]);	
    }

    inline int lca(int a, int b) {
        int l = min(pos[a], pos[b]), r = max(pos[a], pos[b]);
        int k = __lg(r - l + 1);
        pii tmp = min(st[l][k], st[r - (1<<k) + 1][k]);
        return tmp.second;
    }

    void add_edge(int u, int v) {
        g[u].eb(v); g[v].eb(u);
    }
} lca;

