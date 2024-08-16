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
#define mod 998244353
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


const int mxN = 505;
int n, J[mxN], invJ[mxN];
int fp(int a, int b, int p) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
 
void build(int n) {
    J[1] = J[0] = invJ[1] = invJ[0] = 1;
    for(int i = 2; i <= n; i++) J[i] = J[i - 1] * i % mod;
    invJ[n] = fp(J[n], mod - 2, mod);
    for(int i = n - 1; i >= 2; i--) invJ[i] = invJ[i + 1] * (i + 1) % mod;
}
 
int C(int n, int m) {
	if (n < m) return 0;
    if(n == m or m == 0) return 1;
    int res = J[n] * invJ[n - m] % mod * invJ[m] % mod;
    return res;
}

inline void solve() {
  int n; cin >> n;
  vector<int> p(n);
  for (int &i : p) cin >> i;

  int mn = inf;
  vector<int> bk;
  for (int i = 0; i < n; i++) {
    if (p[i] < mn) {
      if (i > 0) bk.eb(i-1);
      mn = p[i];
    }
  }
  bk.eb(n-1);

  test(SZ(bk));

  vector<int> ess_cnt, inter_cnt;
  for (int i = 0; i < SZ(bk); i++) {
    int l = 0;
    if (i) l = bk[i-1] + 1;
    int r = bk[i];
    int res = 0;
    int inter_res = 0;

    for (int j = l; j <= r; j++) {
      for (int c = 0; c < l; c++) {
        if (p[c] > p[j]) res++;
      }
      for (int c = l; c < j; c++) {
        if (p[c] > p[j]) inter_res++;
      }
    }

    ess_cnt.eb(res);
    inter_cnt.eb(inter_res);
    test(res, inter_res);
  }

  vector<int> dp(n + 1, 0);
  dp[0] = 1;

  for (int i = 0; i < SZ(ess_cnt); i++) {
    for (int sz = 1; sz <= n; sz++) {
      if (sz > ess_cnt[i] + inter_cnt[i]) break;
      int a = ess_cnt[i], b = inter_cnt[i];
      int st = (i != 0);
      int res = 0;
      for (int j = st; j <= sz; j++) {
        if (a < j || sz - j > b) continue;
        res = (res + C(a, j) * C(b, sz - j) % mod) % mod;
      }
      for (int j = n; j >= sz; j--) dp[i] = (dp[i] + dp[i-sz] * res % mod) % mod;
    }
  }

  for (int i = 1; i <= n; i++) cout << dp[i] << ' ';
}

signed main() {
	IO;	
	solve();	
}
