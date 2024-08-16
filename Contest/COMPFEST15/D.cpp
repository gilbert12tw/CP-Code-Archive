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
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

int dp[100001][11][11];

inline void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> a(n, vector<int>(m + 1));
  for (int i = 0; i < n; i ++) {
    for (int j = 1; j <= m; j++) 
      cin >> a[i][j];
  }

  vector<vector<int>> srt;
  for (int i = 0; i <= m; i++) {
    vector<int> tmp;
    for (int j = 0; j < n; j++) tmp.eb(a[j][i]);
    sort(ALL(tmp), greater<int>());
    srt.eb(tmp);
  }

  for (int i = min(m, k); i <= m; i++) {
    int mx = 0;
    for (int j = k - 1; j >= 0; j--) {
      int suf = 0;
      for (int rk = 0; rk < n; rk++) {
        suf = max(suf, dp[i-1][k-1][rk]);
      }

      for (int rk = 0; rk < n; rk++) {
        dp[i][j][rk] = srt[i-j][rk] + max(suf, mx); 
        //test(i, j, rk, mx, suf);
        //test(dp[i][j][rk]);
        if (j) suf = max(suf, dp[i-1][j-1][rk]);
      }
      mx = max(mx, suf);
    }
  }
  
  int ans = 0;
  for (int i = k - 1; i >= 0; i--) {
    for (int j = 0; j < n; j++) 
      ans = max(ans, dp[m][i][j]);
  }
  cout << ans;
}

signed main() {
	IO;	
	solve();	
}
