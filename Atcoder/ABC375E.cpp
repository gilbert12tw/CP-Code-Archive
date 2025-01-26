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
  int n; cin >> n;
  vector<int> a(n), b(n);
  int sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
    sum += b[i];
  }
  if (sum % 3 != 0) {
    cout << -1 << '\n';
    return;
  }

  int div_sz = sum / 3;
  vector<vector<int>> dp(div_sz + 1, vector<int>(div_sz + 1, INF));
  dp[0][0] = 0;
  for (int i = 0; i < n; i++) {
    vector<vector<int>> tmp(div_sz + 1, vector<int>(div_sz + 1, INF));
    for (int j = 0; j <= div_sz; j++) {
      for (int k = 0; k <= div_sz; k++) {
        if (dp[j][k] == -1) continue;
        if (j + b[i] <= div_sz)
          ckmin(tmp[j + b[i]][k], dp[j][k] + (a[i] != 1));
        if (k + b[i] <= div_sz)
          ckmin(tmp[j][k + b[i]], dp[j][k] + (a[i] != 2));
        ckmin(tmp[j][k], dp[j][k] + (a[i] != 3));
      }
    }
    dp = tmp;
  }
  int ans = dp[div_sz][div_sz];
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
