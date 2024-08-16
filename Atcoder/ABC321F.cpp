#include<bits/stdc++.h>
//#define loli
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

int q, k;

#define ls (id<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
vector<int> seg[5000 * 4 + 5];

void modify(int a, int b, int x, int l = 1, int r = q, int id = 1) {
  if (a <= l && r <= b) {
    test(l, r, x, id);
    seg[id].eb(x);
    return;
  }
  if (a <= mid) modify(a, b, x, l, mid, ls);
  if (b > mid) modify(a, b, x, mid+1, r, rs);
}

int dp[5001];

void dfs(int id = 1, int l = 1, int r = q) {
  test(id, l, r);

  vector<int> tmp(k + 1);
  for (int i = 0; i <= k; i++) tmp[i] = dp[i];

  for (int x : seg[id]) {
    test(x);
    for (int i = k; i >= x; i--) {
      dp[i] += dp[i-x];
      if (dp[i] > mod) dp[i] %= mod;
    }
  }

  if (l != r) {
    dfs(ls, l, mid);
    dfs(rs, mid+1, r);
  } else if (l == r) {
    cout << dp[k] << '\n';
  }

  // undo
  for (int i = 0; i <= k; i++) dp[i] = tmp[i];
}
inline void solve() {
  cin >> q >> k;
  map<int, vector<int>> mp;
  for (int i = 1; i <= q; i++) {
    char c; int x; 
    cin >> c >> x;
    if (c == '+') {
      mp[x].eb(i);
    } else {
      int lst = mp[x].back();
      mp[x].pop_back();
      modify(lst, i - 1, x);
    }
  }
  for (auto [x, v] : mp) {
    for (int i : v) {
      modify(i, q, x);
    }
  }
  dp[0] = 1;
  dfs();
}

signed main() {
	IO;	
	solve();	
}
