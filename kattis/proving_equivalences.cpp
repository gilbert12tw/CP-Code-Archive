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

// returns component identifier, and topological sort of them.
pair<vector<int>,vector<int>> strongly_cc(const vector<vector<int>> &g){
  int timer = 0, n = g.size();
  vector<int> disc(n), comp(n, -1), topo;
  stack<int> s;

  auto dfs = [&](auto self,int x) -> int {
    int low = disc[x] = ++timer;
    s.push(x);
    for(auto y : g[x])
      if(comp[y] == -1)
        low = min(low,disc[y]?:self(self,y));
    if(low == disc[x]){
      topo.push_back(x);
      for(int y = -1; y != x;){
        comp[y = s.top()] = x;
        s.pop();
      }
    }
    return low;
  };

  for(int i = 0; i < n; ++i)
    if(!disc[i])
      dfs(dfs,i);

  reverse(topo.begin(), topo.end());

  return {comp, topo};
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n);
    vector<pii> tmp;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].eb(v);
        tmp.eb(u, v);
    }
    auto [cid, topo] = strongly_cc(G);

    if (SZ(topo) == 1) {
        cout << 0 << '\n';
        return;
    }

    vector<int> ind(n), out(n);
    for (auto [u, v] : tmp)
        out[cid[u]]++, ind[cid[v]]++;

    int out0 = 0, in0 = 0;
    for (int i : topo) {
        if (ind[i] == 0) in0++;
        if (out[i] == 0) out0++;
    }
    cout << max(in0, out0) << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
