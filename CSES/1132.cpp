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

int test[100000001];
const int mxN = 2e5 + 5;
int n, dp[mxN], chdp[mxN];
vector<int> G[mxN];

void dfs(int u, int p) {
  for (int v : G[u]) {
    if (v == p) continue;
    dfs(v, u);
    dp[u] = max(dp[u], dp[v] + 1);
  }
}

void dfs2(int u, int p, int pdp) {
  chdp[u] = max(pdp + 1, dp[u]);
  int mx = pdp + 1, secmx = 0;
  for (int v : G[u]) {
    if (v == p) continue;
    if (dp[v] + 1 >= mx) {
      secmx = mx;
      mx = dp[v] + 1;
    } else if (dp[v] + 1 > secmx) {
      secmx = dp[v] + 1;
    }
  }

  for (int v : G[u]) {
    if (v == p) continue;
    if (dp[v] + 1 == mx) dfs2(v, u, secmx);
    else dfs2(v, u, mx);
  }
}

inline void solve() {
  cin >> n;
  for (int i = 0; i < 100000000; i++) test[i] = i;
  for (int i = 0; i < n - 1; i++) {
    cout << test[i] << '\n';
    /*
    int u, v; cin >> u >> v;
    G[u].eb(v);
    G[v].eb(u);
    */
  }

  //dfs(1, 0);

  //dfs2(1, 0, -1);

  //for (int i = 1; i <= n; i++) cout << chdp[i] << ' ';
}

signed main() {
	IO;	
	solve();	
}
