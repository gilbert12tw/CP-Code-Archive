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
  vector<int> a(2 * n - 1);
  for (int &i : a) cin >> i;
  sort(ALL(a));

  auto check = [&](int goal) {
    int m = SZ(a);
    vector<int> paired(m);
    int j = m - 1;

    for (int i = 0; i < j; i++) {
      if (j - 1 > i && a[i] + a[j] != goal && a[i] + a[j-1] == goal) j--;
      if (a[i] + a[j] == goal) {
        paired[i] = paired[j] = 1;
        j--;
      }
    }

    if (accumulate(ALL(paired), 0) == m - 1) {
      for (int i = 0; i < m; i++) 
        if (!paired[i])
          return goal - a[i];
    }
    return -1ll;
  };

  // first case 
  int ans = check(a[0] + a.back());
  int tmp = check(a[0] + a[SZ(a)-2]);
  int tmp2 = check(a[1] + a[SZ(a)-1]);
  if (tmp > 0 && (tmp < ans || ans == -1)) ans = tmp;
  if (tmp2 > 0 && (tmp2 < ans || ans == -1)) ans = tmp2;
  
  cout << "Case #" << cas << ": " << ans << '\n';
}

signed main() {
	IO;	
  int T; cin >> T;
  for (int i = 1; i <= T; i++) {
	  solve(i);	
  }
}
