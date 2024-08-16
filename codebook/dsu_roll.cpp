struct DSU {
  int n;
  vector<int> pa, sz;
  vector<pii> stk;
  DSU(int _n) n(_n), pa(_n+1), sz(_n+1, 1) {
    for (int i=1;i<=n;i++) pa[i] = i;
  }
  int get(int u) { 
    while (u != pa[u]) u = pa[u];
    return u;
  }
  bool merge(int u, int v) {
    u = get(u), v = get(v);
    if (u == v) return 0;
    if (sz[u] > sz[v]) swap(u, v);
    sz[v] += sz[u];
    pa[u] = v;
    stk.eb(u, v);
    return 1;
  }
  int record() { return (int)(stk.size()); }
  void roll_back(int keep_point) {
    while (sz(stk) > keep_point) {
      pa[stk.back().F] = stk.back().F;
      sz[stk.back().S] -= sz[stk.back().F];
      stk.pop_back();
    }
  }
};
