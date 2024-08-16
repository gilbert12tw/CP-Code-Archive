struct GenearlMatching { // 1-base
  int n, ans;
  vector<vector<int>> G; // adjacency matrix
  vector<int> vis, linked, p, q, anslink;

  GenearlMatching(int n_): n(n_), ans(0), 
  G(n_+1, vector<int>(n_+1, 0)), vis(n_+1), linked(n_+1), 
  p(n_+1), q(n_+1), anslink(n_+1) {}

  void add_edge(int u, int v) {
    G[u][v] = G[v][u] = 1;
  }
  void update(int tmp) {
    ans = tmp;
    for (int i = 1; i <= n; i++)
      anslink[i] = linked[i];
  }
  bool match(int u) {
    vis[u] = 1;
    for (int i = 1; i <= n; i++) {
      int v = q[i];
      if (vis[v] || !G[u][v]) continue;
      vis[v] = 1;
      if (!linked[v] || match(linked[v])) {
        linked[v] = u; linked[u] = v;
        return true;
      }
    }
    return false;
  }
  void work() {
    fill(ALL(linked), 0);
    int tmp = 0;
    for (int i = 1; i <= n; i++)
      if (!linked[p[i]])
        for (int t = 1; t <= 5; t++) {
          fill(ALL(vis), 0);
          if (match(p[i])) {
            tmp++; break;
          } else {
            for (int j = 1; j <= n; j++) {
              int k = j + rand() % (n - j + 1);
              swap(q[j], q[k]);
            }
          }
        }
    if (tmp > ans)
      update(tmp);
  }
  void solve(int testtimes = 5) {
    srand(541213);
    for (int i = 1; i <= n; i++)
      p[i] = q[i] = i;
    while (testtimes--) {
      for (int i = 1; i <= n; i++) {
        int j = i + rand() % (n - i + 1);
        swap(p[i], p[j]);
        j = i + rand() % (n - i + 1);
        swap(q[i], q[j]);
      }
      work();
    }
  }
  vector<pair<int, int>> get_answer() {
    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++) {
      if (anslink[i] > i) 
        ans.emplace_back(i, anslink[i]);
    }
    return ans;
  }
};
