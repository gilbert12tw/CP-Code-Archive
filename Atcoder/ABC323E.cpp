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

inline int fp(int a, int b, int p) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
 
inline int inv(int x) {return fp(x, mod - 2, mod);}

inline void solve() {
  int n, x;
  cin >> n >> x;
  vector<int> t(n);
  for (int &i : t) cin >> i;
  vector<int> dp(x + 1, 0);
  dp[0] = 1;
  
  int invn = inv(n);

  for (int j = 0; j <= x; j++) {
    for (int i = 0; i < n; i++) {
      if (j >= t[i])
        dp[j] = (dp[j] + dp[j-t[i]] * invn % mod) % mod;
    }
  }

  int ans = 0;
  for (int i = max(0ll, x - t[0] + 1); i <= x; i++) {
    ans = (ans + dp[i] * invn % mod) % mod;
  }
  cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
