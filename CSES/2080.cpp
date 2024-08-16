#include <bits/stdc++.h>
using namespace std;

struct CentroidTree {
  vector<vector<pair<int, int>>> tree;

  vector<int> del, pa, sz, cnt;

  CentroidTree(int n)
      : tree(n + 1, vector<pair<int, int>>()), del(n + 1), pa(n + 1),
        sz(n + 1, 1), cnt(n + 1, 0) {}

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

  void dfs_ans(vector<int> &path, int k, int u, int p = -1, int len = 1) {
    if (len > k)
      return;
    path.emplace_back(len);
    for (auto [v, w] : tree[u]) {
      if (v == p || del[v])
        continue;
      dfs_ans(path, k, v, u, len + w);
    }
  }

  // build the centroid tree recursively
  int build(int u, int k, long long &ans) {
    get_sz(u, -1);
    int centroid = get_centroid(u, sz[u], -1);
    del[centroid] = 1;

    // count path go through centroid
    cnt[0] = 1;
    int mx_depth = 0; // for clear up the array cnt
    for (auto [v, w] : tree[centroid]) {
      if (del[v])
        continue;
      vector<int> path_len;
      dfs_ans(path_len, k, v, -1, 1);
      for (int len : path_len) {
        ans += cnt[k - len];
        mx_depth = max(mx_depth, len);
      }
      for (int len : path_len) {
        cnt[len]++;
      }
    }
    // clear the array cnt
    for (int i = 0; i <= mx_depth; i++)
      cnt[i] = 0;

    for (auto [v, w] : tree[centroid]) {
      if (del[v])
        continue;
      build(v, k, ans);
    }
    return centroid;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, k;
  cin >> n >> k;
  CentroidTree CD(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    CD.add_edge(u, v);
  }

  long long ans = 0;
  CD.build(1, k, ans);
  cout << ans;
}
