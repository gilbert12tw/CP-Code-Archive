#include<bits/stdc++.h>
#define loli
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

class TwoSat { // test @ CSES Giant Pizza
private:
  int n; vector<vector<int>> G, rG, sccs;
  vector<int> ord, idx, vis, res;
  void dfs(int u) {
    vis[u] = true;
    for (int v : G[u]) if (!vis[v]) dfs(v);
    ord.push_back(u);
  }
  void rdfs(int u) {
    vis[u] = false; idx[u] = sccs.size() - 1;
    sccs.back().push_back(u);
    for (int v : rG[u]) if (vis[v]) rdfs(v);
  }
public:
  TwoSat(int n_) : n(n_), G(n), rG(n), idx(n), vis(n), res(n) {}
  void add_edge(int u, int v) {
    G[u].push_back(v); rG[v].push_back(u);
  }
  void pop_edge(int u, int v) {
    G[u].pop_back(); rG[v].pop_back();
  }
  void orr(int x, int y) { // x or y
    if ((x ^ y) == 1) return; // x' = x ^ 1
    add_edge(x ^ 1, y); add_edge(y ^ 1, x);
  }
  void unor(int x, int y) {
    pop_edge(x ^ 1, y); pop_edge(y ^ 1, x);
  }
  bool solve() {
    // clear
    ord.clear(); sccs.clear();
    vis.assign(n, 0);
    for (int i = 0; i < n; ++i) if (not vis[i]) dfs(i);
    reverse(ord.begin(), ord.end());
    for (int u : ord)
      if (vis[u]) sccs.emplace_back(), rdfs(u);
    for (int i = 0; i < n; i += 2)
      if (idx[i] == idx[i + 1]) return false;
    vector<bool> c(sccs.size());
    for (size_t i = 0; i < sccs.size(); ++i)
      for (int z : sccs[i])
        res[z] = c[i], c[idx[z ^ 1]] = !c[i];
    return true;
  }
  bool get(int x) { return res[x]; }
  int get_id(int x) { return idx[x]; }
  int count() { return sccs.size(); }
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    TwoSat ts(n * 2);
    int check = 0;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        int px = (abs(x) - 1) * 2;
        int py = (abs(y) - 1) * 2;
        if (x < 0) px ^= 1; if (y < 0) py ^= 1;
        //test(px, py);
        ts.orr(px, py);
        if (x < 0 && y < 0) check = 1;
    }
    if (!ts.solve()) {
        cout << 0 << '\n';
        return;
    }
    if (!check) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 0; i < 2 * n; i += 2) {
        ts.orr(i, i);
        if (!ts.solve()) {
            cout << 1 << '\n';
            return;
        }
        ts.unor(i, i);
    }
    cout << 2 << '\n';
}

signed main() {
	IO;	
	solve();	
}
