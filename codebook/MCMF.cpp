struct MCMF {
  static const int mxE = 1e5 + 5, mxN = 405;
  int eu[mxE], ev[mxE], w[mxE], cap[mxE], tot;
  vector<int> g[mxN];

  inline void addEdge(int x, int y, int ew, int c) {
    g[x].eb(tot);
    eu[tot] = x; ev[tot] = y; w[tot] = ew; cap[tot++] = c;
    g[y].eb(tot);
    ev[tot] = x; eu[tot] = y; w[tot] = -ew; cap[tot++] = 0;
  }
  // longest path by SPFA
  inline int SPFA(int s, int t, int &ans, int &mxflow) {
    vector<int> dis(mxN, -INF), from(mxN, 0), in(mxN, 0), lim(mxN, 0);
    dis[s] = 0; lim[s] = INF;
    queue<int> q; q.push(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      in[u] = 0;
      for (int i : g[u]) {
        int v = ev[i]; // change this 
        if (cap[i] > 0 && dis[v] < dis[u] + w[i]) {
          dis[v] = dis[u] + w[i];
          lim[v] = min(lim[u], cap[i]); 
          from[v] = i;
          if (!in[v]) q.push(v);
          in[v] = 1;
        }
      }
    }
    if (dis[t] <= -INF) return 0;
    int flcnt = lim[t]; // or ans += dis[t]
    ans += dis[t] * flcnt;
    mxflow += flcnt;
    while (t != s) {
      int e = from[t];	
      cap[e] -= flcnt; cap[e^1] += flcnt; 
      t = eu[e];
    }
    return 1;
  }
  pii run(int s, int t) {
    int ans = 0, fl = 0;
    while (SPFA(s, t, ans, fl));
    return mkp(ans, fl);
  }
} flow;
