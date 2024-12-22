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

class SCC {
public:
  int n, num_;
  vector<vector<int>> G, rG;
  vector<int> ord, num;
  vector<bool> vis;
  void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int v : G[u]) dfs(v);
    ord.push_back(u);
  }
  void rdfs(int u) {
    if (vis[u]) return;
    num[u] = num_; vis[u] = 1;
    for (int v : rG[u]) rdfs(v);
  }
  inline void init(int n_) {
    n = n_, num_ = 0;
    G.clear(); G.resize(n); rG.clear();
    rG.resize(n); vis.clear(); vis.resize(n); num.resize(n);
  }
  inline void add_edge(int st, int ed) {
    G[st].push_back(ed);
    rG[ed].push_back(st);
  }
  void solve() {
    fill(vis.begin(), vis.end(), 0);
    for (int i = 0; i < n; ++i)
      if (not vis[i]) dfs(i);

    reverse(ord.begin(), ord.end());
    fill(vis.begin(), vis.end(), 0);
    for (int i : ord) {
      if (not vis[i]) {
        rdfs(i); num_++;
      }
    }
  }
  inline int get_id(int x) { return num[x]; }
  inline int count() { return num_; }
} scc;

inline void solve() {
    SCC scc;
    int n, m;
    cin >> n >> m;
    scc.init(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        scc.add_edge(u, v);
    }
    scc.solve();
    if (scc.count() == 1) {
        cout << 0 << '\n';
        return;
    }
    set<pii> edge;
    vector<int> stand(n);
    for (int u = 0; u < n; u++) {
        stand[scc.get_id(u)] = u + 1;
        for (int v : scc.G[u]) {
            if (scc.get_id(u) != scc.get_id(v))
                edge.emplace(scc.get_id(u), scc.get_id(v));
        }
    }
    vector<int> ind(n), out(n);
    for (auto [u, v] : edge) ind[u]++, out[v]++;
    int out0 = 0, in0 = 0;
    vector<int> v[2];
    for (int i = 0; i < scc.count(); i++) {
        if (ind[i] == 0) {
            in0++;
            v[0].eb(i);
        }
        if (out[i] == 0) {
            out0++;
            v[1].eb(i);
        }
    }
    cout << max(in0, out0) << '\n';
    if (in0 >= out0) {
        for (int i = 0; i <= out0; i++) {
        }
    } else {
    }
}

signed main() {
    IO; 
    int T = 1;
    while (T--) solve();    
}

