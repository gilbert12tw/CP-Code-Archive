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

template<class T> bool ckmax(T& a, const T& b) { 
  return (b>a) ? a=b, 1 : 0; 
}

inline void solve() {
  int n; cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<vector<int>> dp(n+1, vector<int>(n+1));
  vector<vector<int>> g(n+1, vector<int>(n+1));
  for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++) { 
    dp[i][j] = -1;
    if (i != j) g[i][j] = gcd(a[i], a[j]);
    if ((j - i + 1) == 2) {
      if (g[i][j] > 1) dp[i][j] = g[i][j];
    }
  }

  for (int len = 3; len <= n; len++) {
    for (int i = 1; i + len - 1 <= n; i++) {
      int j = i + len - 1;

      if (g[i][j] > 1 && dp[i+1][j-1] != -1)
        dp[i][j] = g[i][j] + dp[i+1][j-1];
      
      for (int k = i + 1; k < j; k++) {
        int g1 = g[i][k];
        int g2 = g[k][j];
        if (g[i][k] > 1 && g1 > 1 && g2 > 1 && dp[i+1][k-1] != -1 && dp[k+1][j-1] != -1)
          ckmax(dp[i][j], dp[i+1][k-1] + dp[k+1][j-1] + g1 + g2);

        if (dp[i][k] != -1 && dp[k+1][j] != -1) 
          ckmax(dp[i][j], dp[i][k] + dp[k+1][j]);
      }
      //test(i, j, dp[i][j]);
    }
  }
  cout << dp[1][n] << '\n'; 
}

signed main() {
	IO;	
	solve();	
}
