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

inline void solve(int cas) {
  int n; cin >> n;
  vector<int> v(n);
  for (int &i : v) cin >> i;
  sort(ALL(v));
  long double ans = -INF;

  for (int i = 1; i <= 2; i++) 
    for (int j = 1; j <= 2; j++) {
      if (n - i - j != 3 && n - j - 1 > i)
        ans = max(ans, (long double)1.0 * (v[n-1] + v[n-j-1]) / 2.0 - 1.0 * (v[i] + v[0]) / 2.0);
    }

  cout << fixed << setprecision(10);
  cout << "Case #" << cas << ": " << ans << '\n';
}

signed main() {
	IO;	
  int T; cin >> T;
  for (int i = 1; i <= T; i++) solve(i);	
}
