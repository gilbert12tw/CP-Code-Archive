struct CentroidTree {
  vector<vector<pair<int, int>>> tree;

  vector<vector<int>> centroid_tree, dis;
  vector<int> del, pa, sz;

  CentroidTree(int n)
      : tree(n + 1, vector<pair<int, int>>()),
        centroid_tree(n + 1, vector<int>()), dis(n + 1, vector<int>()),
        del(n + 1), pa(n + 1), sz(n + 1, 1) {}

  void add_edge(int u, int v, int w = 1) {
    tree[u].emplace_back(v, w);
    tree[v].emplace_back(u, w);
  }

  void get_sz(int u, int p) {
    sz[u] = 1;
    for (auto [v, w] : tree[u]) {
      if (v == p || del[v])
        continue;
      get_sz(v, u);
      sz[u] += sz[v];
    }
  }

  int get_centroid(int u, int n, int p) {
    for (auto [v, w] : tree[u]) {
      if (v != p && !del[v] && sz[v] > n / 2)
        return get_centroid(v, n, u);
    }
    return u;
  }

  void get_dis(int u, int p, int len) {
    dis[u].emplace_back(len);
    for (auto [v, w] : tree[u]) {
      if (v == p || del[v])
        continue;
      get_dis(v, u, len + w);
    }
  }

  // build the centroid tree recursively
  int build(int u = 1) {
    get_sz(u, -1);
    int centroid = get_centroid(u, sz[u], -1);
    del[centroid] = 1;
    get_dis(centroid, -1, 0);

    // so something

    for (auto [v, w] : tree[centroid]) {
      if (del[v])
        continue;
      int tcd = build(v);
      pa[tcd] = centroid;
      centroid_tree[centroid].emplace_back(tcd);
    }
    return centroid;
  }

  void upd(int x) {
    int u = x, lst = 0;
    for (int i = dis[x].size() - 1; i >= 0; i--) {
      int dist = dis[x][i];
      // do something
      lst = u;
      u = pa[u];
    }
  }

  int qry(int x) {
    int u = x, res = 0, lst = 0;
    for (int i = dis[x].size() - 1; i >= 0; i--) {
      int dist = dis[x][i];
      // do something
      lst = u;
      u = pa[u];
    }
    return res;
  }
};
