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
  int a, b, c;
  cin >> a >> b >> c;

  // cheese = s + 2 * d
  // buns = 2 * s + 2 * d

  auto biggest = [](int cheese, int buns) {
    return min(cheese, buns - 1);
  };

  auto check = [&](int s) { // return [cheese, buns];
    if (c < s * a) return (int)-1;
    int d = (c - s * a) / b;
    return biggest(s + 2 * d, 2 * (s + d));
  };

  
  int l = 0, r = c / a;

  int d = 1000000;
  int ans = 0;
  for (int i = l; i <= l + d && i <= r; i++) {
    if (check(i) == -1) break;
    ans = max(ans, check(i));
  }

  for (int i = r; i >= r - d && i >= 0; i--) {
    if (check(i) == -1) break;
    ans = max(ans, check(i));
  }

  cout << "Case #" << cas << ": " << ans << '\n';
}

signed main() {
	IO;	
  int T; cin >> T;
  for (int i = 1; i <= T; i++) {
	  solve(i);	
  }
}
