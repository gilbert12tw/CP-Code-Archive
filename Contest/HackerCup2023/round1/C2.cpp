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
  vector<vector<int>> div(n + 1, vector<int>());
  vector<int> pressed(n + 1, 0);
  string s; cin >> s;

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) 
      div[j].eb(i);
  }

  
  int ans = 0;
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    int o = (s[i-1] == '1');
    int res = o;
    for (int j : div[i]) {
      res += (pressed[j]);
    }
    if (res % 2) {
      pressed[i]++;
      ans++;
    }
  }


  int q;
  cin >> q;
  while (q--) {
    int x; cin >> x;
    if (pressed[x]) ans--;
    else ans++;
    pressed[x] ^= 1;
    sum += ans;
  }
  cout << "Case #" << cas << ": " << sum << '\n';
}

signed main() {
	IO;	
  int T; cin >> T;
  for (int i = 1; i <= T; i++) solve(i);	
}
