// Tree knapsack
void dfs(int u) {
  sz[u] = 1;
  for (int v : tree[u]) {
    dfs(v);
    for (int i = sz[u] + sz[v]; i >= 1; i--)
      for (int j = max(1, i - sz[u]); j<=i && j<=sz[v]; j++)
        dp[u][i] = min(dp[u][i], dp[u][i-j] + dp[v][j]);	
    sz[u] += sz[v];
  }
}
