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
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  vector<pii> dp((1<<m) + 1);
  vector<pii> dp_sec((1<<m) + 1);
  
  auto update = [&](int idx, pii p) -> void {
    if (p >= dp[idx]) {
      dp_sec[idx] = dp[idx];
      dp[idx] = p;
    } else if (p > dp_sec[idx]) {
      dp_sec[idx] = p;
    }
  };

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      if (s[j] == 'Y')
        a[i] |= (1<<j);
    }
    update(a[i], mkp(__builtin_popcount(a[i]), -i));
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < (1<<m); j++) {
      if (!get_bit(j, i)) {
        update(j, dp[j ^ (1 << i)]);
        update(j, dp_sec[j ^ (1 << i)]);
      }
    }
  }

  int msk = (1<<m) - 1;

  int mx = 0;
  pii ans_idx(n, n);

  auto check = [&](int idx, pii p) -> void {
    pii id = mkp(min(idx, -p.second), max(idx, -p.second));
    int sum = p.first + __builtin_popcount(a[idx]);
    if (mx < sum || (mx == sum && id < ans_idx)) {
      mx = sum;
      ans_idx = id;
    }
  };

  for (int i = 0; i < n; i++) {
    int rm = msk ^ a[i];
    if (dp[rm].first != 0 && dp[rm].second != -i) {
      check(i, dp[rm]);
    } else if (dp_sec[rm].first != 0 && dp_sec[rm].second != -i) {
      check(i, dp_sec[rm]);
    }
  }

  if (mx != 0) {
    cout << ans_idx.first + 1 << ' ' << ans_idx.second + 1 << '\n';
  } else {
    cout << "No\n";
  }
}

signed main() {
	IO;	
	solve();	
}
