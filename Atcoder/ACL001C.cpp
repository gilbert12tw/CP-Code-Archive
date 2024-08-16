#include<bits/stdc++.h>
//#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
#define vi vector<int>
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - x.begin())
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

struct MCMF {
  static const int mxE = 1e7+5, mxN = 50005;
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
    test(dis[t]);
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

inline void solve() {
  int n, m;
  cin >> n >> m;
  vector<string> mat(n);

  for (int i = 0; i < n; i++) {
    cin >> mat[i];
  }

  int s = n * m * 2 + 5, t = s + 1;

  auto code = [&n, &m](int x, int y, int type) {
    return x * m + y + type * n * m;
  };

  auto bfs = [&](int x, int y) {
    queue<pii> q;
    q.push(x, y);
    vector<vector<int>> dis(n, vector<int>(m, inf));
    dis[x][y] = 0;

    while (!q.empty()) {
      auto now = q.front(); q.pop();
      int d = dis[now.X][now.Y];
      //test(x, y, d);

      flow.addEdge(code(x, y, 0), code(now.X, now.Y, 1), d, 1);

      if (now.X + 1 < n && mat[now.X+1][now.Y] != '#' && dis[now.X+1][now.Y] > d + 1) {
        dis[now.X+1][now.Y] = d + 1;
        q.push(now.X + 1, now.Y);
      }
      if (now.Y + 1 < m && mat[now.X][now.Y+1] != '#' && dis[now.X][now.Y+1] > d + 1) {
        dis[now.X][now.Y+1] = d + 1;
        q.push(now.X, now.Y + 1);
      }
    }
  };

  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      if (mat[x][y] == 'o') { 
        bfs(x, y);
        flow.addEdge(s, code(x, y, 0), 0, 1);
      }
      if (mat[x][y] != '#') flow.addEdge(code(x, y, 1), t, 0, 1);
      test(code(x, y, 0));
      test(code(x, y, 1));
    }
  }
  cout << flow.run(s, t).first << '\n';
}

signed main() {
	IO;	
	solve();	
}
