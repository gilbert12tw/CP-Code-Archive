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

inline void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<array<int, 3>> edge;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edge.pb({a, b, c});
  }

  vector<int> del(m);
  vector<pii> qry;
  for (int i = 0; i < q; i++) {
    int o, a, b;
    cin >> o;
    if (o == 1) {
      cin >> a;
      qry.eb(a - 1, 0);
      del[a - 1] = 1;
    } else {
      cin >> a >> b;
      qry.eb(a, b);
    }
  }

  vector<vector<int>> mat(n + 1, vector<int>(n + 1, INF));
  for (int i = 1; i <= n; i++) mat[i][i] = 0;
  for (int i = 0; i < m; i++) {
    if (del[i]) continue;
    ckmin(mat[edge[i][0]][edge[i][1]], edge[i][2]);
    ckmin(mat[edge[i][1]][edge[i][0]], edge[i][2]);
  }

  // floyd
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
      }
    }
  }

  vector<int> ans;
  reverse(ALL(qry));
  for (auto [x, y] : qry) {
    if (y == 0) {
      // add edge x
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          mat[i][j] = min(mat[i][j], mat[i][edge[x][0]] + mat[edge[x][1]][j] + edge[x][2]);
          mat[i][j] = min(mat[i][j], mat[i][edge[x][1]] + mat[edge[x][0]][j] + edge[x][2]);
        }
      }
    } else {
      ans.eb(mat[x][y]);
    }
  }
  reverse(ALL(ans));
  for (int i : ans) cout << (i == INF ? -1 : i) << '\n';
}

signed main() {
	IO;	
	solve();	
}
