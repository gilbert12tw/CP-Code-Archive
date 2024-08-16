struct BCC {
  int n, dfc, num, tp, cnt;
  vector<int> dfn, low, stk;
  vector<vector<int>> g, tree;

  BCC(int _n): n(_n), dfc(0), num(0), tp(0),
  cnt(_n), dfn(_n+1), low(_n+1), stk(_n+1),
  g(_n+1, vector<int>()), tree((_n+1) * 2, vector<int>())
  {}

  void add_edge(int u, int v) {
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  void Tarjan(int u) { 
    low[u] = dfn[u] = ++dfc;
    stk[++tp] = u;
    ++num;
    for (int v : g[u]) {
      if (!dfn[v]) {
        Tarjan(v);
        low[u] = min(low[u], low[v]);
        if (low[v] == dfn[u]) {
          cnt++; // cnt init to N
          for (int x = 0; x != v; --tp) {
            x = stk[tp];
            tree[cnt].push_back(x);
            tree[x].push_back(cnt);
          }
          tree[cnt].push_back(u);
          tree[u].push_back(cnt);
        }
      } else { low[u] = min(low[u], dfn[v]); }
    }
  }
};
