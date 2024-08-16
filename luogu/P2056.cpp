#include <bits/stdc++.h>
using namespace std;

struct CentroidTree {
  vector<vector<pair<int, int>>> tree;

  vector<vector<int>> centroid_tree, dis;
  vector<int> del, pa, sz;

  // for this problem
  int blk_cnt = 0;
  vector<priority_queue<int>> pa_con, pa_del, mx, mx_del;
  multiset<int> diameter;

  CentroidTree(int n)
      : tree(n + 1, vector<pair<int, int>>()),
        centroid_tree(n + 1, vector<int>()), dis(n + 1, vector<int>()),
        del(n + 1), pa(n + 1), sz(n + 1, 1) {
    mx.resize(n + 1);
    mx_del.resize(n + 1);
    pa_con.resize(n + 1);
    pa_del.resize(n + 1);
  }

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
    del[centroid] = 1; // delete centroid
    get_dis(centroid, -1, 0);

    for (auto [v, w] : tree[centroid]) {
      if (del[v])
        continue;
      int tcd = build(v);
      pa[tcd] = centroid;
      centroid_tree[centroid].emplace_back(tcd);
    }
    return centroid;
  }

  void lazy_delete(priority_queue<int> &pq, priority_queue<int> &del) {
    while (!pq.empty() && !del.empty() && pq.top() == del.top()) {
      pq.pop();
      del.pop();
    }
  }

  int get_diameter(int x) {
    lazy_delete(mx[x], mx_del[x]);
    if (mx[x].size() == 0)
      return -1;

    int res = 0, tmp = 0;
    tmp = mx[x].top();
    mx[x].pop();
    lazy_delete(mx[x], mx_del[x]);

    if (mx[x].size() == 0) {
      mx[x].push(tmp);
      return -1;
    }

    res = tmp + mx[x].top();
    mx[x].push(tmp);
    return res;
  }

  void add_diameter(int x) {
    int diam = get_diameter(x);
    if (diam == -1)
      return;
    diameter.insert(diam);
  }

  void del_diameter(int x) {
    int diam = get_diameter(x);
    if (diam == -1)
      return;
    diameter.erase(diameter.find(diam));
  }

  void add(int x, int col) {
    del_diameter(x);
    if (col) {
      blk_cnt++;
      mx[x].push(0);
    } else {
      blk_cnt--;
      mx_del[x].push(0);
    }
    add_diameter(x);

    int u = pa[x], lst = x;
    for (int i = dis[x].size() - 2; i >= 0; i--) {
      int dist = dis[x][i];
      del_diameter(u);
      if (col) {
        lazy_delete(pa_con[lst], pa_del[lst]);
        if (!pa_con[lst].empty())
          mx_del[u].push(pa_con[lst].top());
        pa_con[lst].push(dist);
        mx[u].push(pa_con[lst].top());
      } else {
        mx_del[u].push(pa_con[lst].top());
        pa_del[lst].push(dist);
        lazy_delete(pa_con[lst], pa_del[lst]);
        if (!pa_con[lst].empty())
          mx[u].push(pa_con[lst].top());
      }
      add_diameter(u);

      lst = u;
      u = pa[u];
    }
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n;
  vector<int> col(n + 1);
  CentroidTree CD(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    CD.add_edge(u, v);
  }

  CD.build();

  for (int i = 1; i <= n; i++) {
    col[i] = 1;
    CD.add(i, col[i]);
  }

  cin >> m;
  while (m--) {
    char c;
    int x;
    cin >> c;
    if (c == 'C') {
      cin >> x;
      col[x] ^= 1;
      CD.add(x, col[x]);
    } else {
      if (CD.blk_cnt == 0)
        cout << -1 << '\n';
      else if (CD.blk_cnt == 1)
        cout << 0 << '\n';
      else
        cout << *CD.diameter.rbegin() << '\n';
    }
  }
}
