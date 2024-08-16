#include<bits/stdc++.h>
//#define loli
using namespace std;
#define int __int128
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

int p2[100];
inline int down_k(int n, int x, int k) {
  if (k > 80) return 0;
  int level = p2[k];
  x *= level;
  return max(int(0), min(level, n - x + 1));
}

inline void solve() {
  long long tn, tx, tk;
  cin >> tn >> tx >> tk;

  int n, x, k;
  n = tn; x = tx; k = tk;

  int from = x;
  int ans = down_k(n, x, k);

  x = x / 2;
  k--;

  while (x != 0 && k >= 0) {
    if (k == 0) {
      ans++;
      break;
    }
    
    if (from == x * 2) {
      ans += down_k(n, x * 2 + 1, k - 1);
    } else {
      ans += down_k(n, x * 2, k - 1);
    }
    from = x;
    x /= 2;
    k--;
  }
  unsigned long long out = ans;
  cout << out << '\n';
}

signed main() {
	IO;	
  long long T; cin >> T;
  p2[0] = 1;
  for (int i = 1; i <= 80; i++) p2[i] = p2[i-1] * 2;
	while (T--) solve();	
}
