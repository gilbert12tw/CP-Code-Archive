#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e4 + 5;
int col[mxN];

struct CentroidTree {
  vector<vector<pair<int, int>>> tree;

  vector<vector<int>> centroid_tree, dis;
  vector<int> del, pa, sz;

  // for this problem
  vector<int> sum[2], cnt[2], subsum[2], subcnt[2];

  CentroidTree(int n)
      : tree(n + 1, vector<pair<int, int>>()),
        centroid_tree(n + 1, vector<int>()), dis(n + 1, vector<int>()),
        del(n + 1), pa(n + 1), sz(n + 1, 1) {
    sum[0].resize(n + 1);
    sum[1].resize(n + 1);
    cnt[0].resize(n + 1);
    cnt[1].resize(n + 1);
    subsum[0].resize(n + 1);
    subsum[1].resize(n + 1);
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
  int build(int u) {
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

  void upd(int x, int col, int toggle) { // call build() before upd
    int u = x, lst = 0;
    for (int i = dis[x].size() - 1; i >= 0; i--) {
      int dist = dis[x][i]; // dist is the distance between x, u
      if (lst) {
        subsum[col][lst] += dist;
        if (toggle)
          subsum[col ^ 1][lst] -= dist;
      }
      sum[col][u] += dist;
      cnt[col][u]++;
      if (toggle) {
        sum[col ^ 1][u] -= dist;
        cnt[col ^ 1][u]--;
      }
      lst = u;
      u = pa[u];
    }
  }

  int qry(int x, int col) { // call build() before qry
    int u = x, res = 0, lst = 0;
    for (int i = dis[x].size() - 1; i >= 0; i--) {
      int dist = dis[x][i]; // dist is the distance between x, u
      if (lst) {
        res += sum[col][u] - subsum[col][lst] +
               (cnt[col][u] - cnt[col][lst]) * dist;
      } else {
        res += sum[col][u] + cnt[col][u] * dist;
      }
      lst = u;
      u = pa[u];
    }
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  CentroidTree CD(n);

  for (int i = 1; i <= n; i++) {
    cin >> col[i];
  }

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    CD.add_edge(u, v);
  }

  CD.build(1);

  for (int i = 1; i <= n; i++) {
    CD.upd(i, col[i], 0); // toggle = 0
  }

  while (m--) {
    int o, x;
    cin >> o >> x;
    if (o == 1) {
      col[x] ^= 1;
      CD.upd(x, col[x], 1); // toggle = 1
    } else {
      cout << CD.qry(x, col[x]) << '\n';
    }
  }
}
