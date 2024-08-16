#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5 + 5;
int sz[mxN];
vector<int> g[mxN];

void get_sz(int u, int p) {
  sz[u] = 1;
  for (int v : g[u]) {
    if (v == p)
      continue;
    get_sz(v, u);
    sz[u] += sz[v];
  }
}

int get_centroid(int u, int n, int p) {
  for (int v : g[u]) {
    if (v != p and sz[v] > n / 2)
      return get_centroid(v, n, u);
  }
  return u;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  get_sz(1, -1);
  cout << get_centroid(1, n, -1);
}
