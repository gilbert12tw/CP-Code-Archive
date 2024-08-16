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
};
