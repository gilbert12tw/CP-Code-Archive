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
#define MOD 998244353
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
  int n;
  string t;
  cin >> n >> t;
  vector<string> s(n);
  int mx_length = SZ(t);
  for (auto &i : s) { 
    cin >> i;
    ckmax(mx_length, SZ(i));
  }

  vector<int> lcnt(mx_length + 1), rcnt(mx_length + 1);
  int ans = 0;
  for (auto str : s) {
    int p = -1;
    for (int i = 0; i < SZ(str); i++) {
      if (p + 1 < SZ(t) && t[p+1] == str[i]) p++;
    }
    lcnt[p+1]++;

    p = 0;
    for (int i = SZ(str) - 1; i >= 0; i--) {
      if (p + 1 <= SZ(t) && t[SZ(t) - p - 1] == str[i]) p++;
    }
    rcnt[p]++;
  }

  for (int i = 1; i <= mx_length; i++) {
    lcnt[i] += lcnt[i-1];
  }
  for (int i = 0; i <= mx_length; i++) {
    ans = ans + rcnt[i] * (lcnt[mx_length] - ((SZ(t) - i - 1 < 0) ? 0 : lcnt[SZ(t) - i - 1]));
  }
  cout << ans << '\n';

}

signed main() {
	IO;	
	solve();	
}
