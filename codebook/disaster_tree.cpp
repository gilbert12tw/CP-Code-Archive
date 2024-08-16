class DisasterTree {
  static const int N = 2e5 + 5;
  public:
  int n, m;
  vector<int> g[N], tp;
  int pa[20][N], dep[mxN], vis[N];

  void add_edge(int u, int v) {
    g[u].eb(v);
  }

  int lca(int u, int v) {
    if (u == v) return u;
    if (dep[u] < dep[v]) 
      swap(u, v);
    for (int i = 18; i >= 0; i--) {
      if (pa[i][u] && dep[pa[i][u]] >= dep[v]) {
        u = pa[i][u];
      }
    }
    if (u == v) return u;
    for (int i = 18; i >= 0; i--) {
      if (pa[i][u] && pa[i][v] && pa[i][u] != pa[i][v]) {
        u = pa[i][u];
        v = pa[i][v];
      }
    }
    return pa[0][u];
  }

  void topo(int u) {
    vis[u] = 1;
    for (int v : g[u]) {
      if (!vis[v]) topo(v);
    }
    tp.eb(u);
  }

  void build(int st) {
    tp.clear();
    topo(st);
    reverse(ALL(tp));

    for (int u : tp) {
      if (u == st) dep[u] = 0;
      else dep[u] = dep[pa[0][u]] + 1;
      for (int i = 1; i <= 18; i++) {
        pa[i][u] = pa[i-1][pa[i-1][u]];
      }
      for (int v : g[u]) {
        if (pa[0][v]) 
          pa[0][v] = lca(pa[0][v], u);
        else 
          pa[0][v] = u;
      }
    }
  }
} tree;
