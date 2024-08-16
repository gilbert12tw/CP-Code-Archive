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

int ok = 0;
vector<int> ans, tmp;

void dfs(int u, int lst, int sum) {
  if (sum > 41) return;
  if (ok && SZ(tmp) >= SZ(ans)) return;

  if (u == 1 && sum <= 41) {
    ok = 1;
    while (sum < 41) {
      tmp.eb(1);
      sum++;
    }
    if (ans.empty() || SZ(ans) > SZ(tmp))
      ans = tmp;
    return;
  }
  for (int i = lst; i >= 2; i--) {
    if (u % i) continue;
    tmp.eb(i);
    dfs(u / i, i, sum + i);
    tmp.pop_back();
  }
}

inline void solve(int cas) {
  int n; cin >> n;
  ok = 0;
  ans.clear();
  tmp.clear();

  dfs(n, min(41ll, n), 0);
    
  cout << "Case #" << cas << ": ";
  if (ok) {
    sort(ALL(ans));
    cout << SZ(ans) << ' ';
    for (int i = 0; i < SZ(ans); i++) 
      cout << ans[i] << " \n"[i == SZ(ans)-1];
  } else {
    cout << -1 << '\n';
  }
}

signed main() {
	IO;	
  int T; cin >> T;
  for (int i = 1; i <= T; i++) solve(i);	
}
