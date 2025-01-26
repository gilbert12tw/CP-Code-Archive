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
#define mod 998244353
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
  vector<int> b(n);
  for (int &i : b) {
    cin >> i;
    if (i != -1) i = m - i + 1;
  }
  re(b);

  vector<vector<int>> dp_sum(n, vector<int>(m + 1, 0));
  vector<vector<int>> dp_cnt(n, vector<int>(m + 1, 0));

  if (b[0] == -1) {
    for (int i = 1; i <= m; i++) {
      dp_sum[0][i] = 1;
      dp_cnt[0][i] = 1;
    }
  } else {
    dp_sum[0][b[0]] = 1;
    dp_cnt[0][b[0]] = 1;
  }

  for (int i = 1; i < n; i++) {
    vector<int> sum(m + 1), cnt(m + 1);
    for (int j = 1; j <= m; j++) {
      sum[j] = (sum[j-1] + dp_sum[i-1][j]) % mod;
      cnt[j] = (cnt[j-1] + dp_cnt[i-1][j]) % mod;
    }

    if (b[i] == -1) {
      for (int j = 1; j <= m; j++) {
        dp_sum[i][j] = dp_sum[i-1][j] * (m - j + 1) % mod;
        dp_cnt[i][j] = dp_cnt[i-1][j] * (m - j + 1) % mod;

        int ps = (sum[m] - sum[j] + mod) % mod;
        int pc = (cnt[m] - cnt[j] + mod) % mod;
        dp_sum[i][j] = (ps + pc + dp_sum[i][j]) % mod;
        dp_cnt[i][j] = (pc + dp_cnt[i][j]) % mod;
      }
    } else {
      for (int j = 1; j <= b[i]; j++) {
        dp_sum[i][j] = dp_sum[i-1][j];
        dp_cnt[i][j] = dp_cnt[i-1][j];
      }
      int ps = (sum[m] - sum[b[i]] + mod) % mod;
      int pc = (cnt[m] - cnt[b[i]] + mod) % mod;
      test(i, ps, pc);
      dp_sum[i][b[i]] = (ps + pc + dp_sum[i][b[i]]) % mod;
      dp_cnt[i][b[i]] = (pc + dp_cnt[i][b[i]]) % mod;
    }

    test(i);
    for (int j = 1; j <= m; j++) {
      test(j, dp_sum[i][j], dp_cnt[i][j]);
    }
  }

  int ans = 0;
  for (int i = 1; i <= m; i++) {
    ans = (ans + dp_sum[n-1][i]) % mod;
  }
  cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
