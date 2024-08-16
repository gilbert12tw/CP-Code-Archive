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

inline void solve() {
  int n; cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  auto check = [&](int b) {
    int sum = 0, prv = 0;
    vector<int> cnt(2), wsum(2);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      int v = get_bit(a[i], b);
      prv = sum;
      sum ^= v;

      wsum[prv] = (wsum[prv] - i) % mod;
      if (wsum[prv] < 0) wsum[prv] += mod;
      cnt[prv]++;

      ans = (ans + cnt[sum ^ 1] * (i + 1) % mod + wsum[sum ^ 1]) % mod;
      ans %= mod;
      if (ans < 0) ans += mod;

    }
    return ans;
  };

  int ans = 0;
  for (int i = 0; i <= 30; i++) {
    ans = (ans + (check(i) * (1LL<<i) % mod)) % mod; 
  }
  cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
