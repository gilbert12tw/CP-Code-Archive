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
  int n, m;
  cin >> n >> m;

  vector<int> a(n + 1), b(m + 1), sum(n + 1);
  vector<vector<int>> nxt(n + 1, vector<int>(m + 1));
  for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i-1] + a[i];
  for (int i = 1; i <= m; i++) cin >> b[i];

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i] > b[j]) {
        nxt[i][j] = -1;
      } else {
        nxt[i][j] = ub(sum, sum[i - 1] + b[j]) - sum.begin() - 1;
      }
    }
  }

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, INF)), cnt(n + 1, vector<int>(m + 1, 0));
  dp[0][0] = 0;
  cnt[0][0] = 1;

  auto madd = [](int &a, int &b) {
    a += b;
    if (a >= mod) a -= mod;
  };

  auto upd = [&](int a, int b, int val, int c) {
    if (dp[a][b] > val) {
      dp[a][b] = val; cnt[a][b] = c;
    } else if (dp[a][b] == val) {
      madd(cnt[a][b], c);
    }
  };


  vector<vector<array<int, 3>>> add(n + 1), del(n + 1);
  vector<map<int, int>> dp_tag(m + 1);
  for (int i = 0; i <= n; i++) {
    // add
    for (auto ar : add[i]) {
      madd(dp_tag[ar[2]][ar[0]], ar[1]);
    }
    
    pii mn = mkp(INF, INF);
    for (int j = 1; j <= m; j++) {
      //dp[i][j] = min(dp[i][j], dp[i][j-1]);
      if (dp[i][j] > dp[i][j-1]) {
        dp[i][j] = dp[i][j-1];
        cnt[i][j] = cnt[i][j-1];
      } else if (dp[i][j] == dp[i][j-1]) {
        //dp[i][j] = dp[i][j-1];
        cnt[i][j] = (cnt[i][j] + cnt[i][j-1]) % mod;
      }

      if (i != n && nxt[i+1][j] != -1) { 
        //dp[nxt[i+1][j]][j] = min(dp[nxt[i+1][j]][j], dp[i][j] + m - j);

        if (nxt[i+1][j] >= i + 1) {
          add[i+1].pb({dp[i][j] + m - j, cnt[i][j], j});
          del[nxt[i+1][j]].pb({dp[i][j] + m - j, cnt[i][j], j});
        }
        /*
           for (int k = i + 1; k <= nxt[i+1][j]; k++) {
           if (dp[k][j] > dp[i][j] + m - j) {
           dp[k][j] = dp[i][j] + m - j;
           cnt[k][j] = cnt[i][j];
           } else if (dp[k][j] == dp[i][j] + m - j) {
           cnt[k][j] = (cnt[k][j] + cnt[i][j]) % mod;
           }
           }
         */
      }
      //test(i, j, dp[i][j]);
    }

    // del
    for (auto ar : del[i]) {
      madd(dp_tag[ar[2]][ar[0]], -ar[1]);
    }
  }
  int ans = *min_element(ALL(dp[n]));
  if (ans == INF) {
    cout << -1 << '\n';
    return;
  }

  int cc = 0;
  for (int j = 1; j <= m; j++) {
    if (dp[n][j] == ans) {
      cc = (cc + cnt[n][j]) % mod;
    }
  }

  cout << ans << ' ' << cc << '\n';
}

signed main() {
  IO;	
  int T; cin >> T;
  while (T--) solve();	
}
