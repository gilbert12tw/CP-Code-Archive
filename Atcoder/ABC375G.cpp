#include<bits/stdc++.h>
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
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

struct Dijkstra {
  static const int mxN = 2e5 + 5;
  int n;
  vector<vector<pii>> g;

  Dijkstra(int _n) : n(_n), g(_n) {}

  void add_edge(int u, int v, int w) {
    g[u].eb(v, w);
    g[v].eb(u, w);
  }

  void dijkstra(int s, vector<int> &dis, vector<int> &cnt) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dis[s] = 0;
    cnt[s] = 1; 
    pq.push(0, s);

    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
      if (d > dis[u]) continue;
      for (auto [v, w] : g[u]) {
        if (dis[v] == -1 || dis[v] > d + w) {
          dis[v] = d + w;
          cnt[v] = cnt[u];
          pq.push(dis[v], v);
        } else if (dis[v] == d + w) {
          cnt[v] = (cnt[v] + cnt[u]) % mod;
        }
      }
    }
  }
};

inline void solve() {
  int n, m;
  cin >> n >> m;
  Dijkstra ss(n+1), ee(n+1);
  vector<array<int, 3>> edge;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    ss.add_edge(a, b, c);
    ee.add_edge(a, b, c);
    edge.pb({a, b, c});
  }
  
  vector<int> cnts(n + 1, 0), diss(n + 1, -1);
  vector<int> cnte(n + 1, 0), dise(n + 1, -1);
  ss.dijkstra(1, diss, cnts);
  ee.dijkstra(n, dise, cnte);

  int sh = diss[n], cc = cnts[n];

  for (auto [a, b, c] : edge) {
    int pth_cnt = 0;
    if (diss[a] + dise[b] + c == sh) {
      pth_cnt = (pth_cnt + cnts[a] * cnte[b] % mod) %mod;
    }
    if (dise[a] + diss[b] + c == sh) {
      pth_cnt = (pth_cnt + cnte[a] * cnts[b] % mod) %mod;
    }
    if (pth_cnt == cc) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }
}

signed main() {
  IO;	
  solve();	
}
