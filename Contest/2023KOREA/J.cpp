#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
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


const vector<int> prime = {2, 3, 5, 7};
vector<vector<int>> states;
map<pair<int, vector<int>>, int> dp;
vector<int> fac;
int goal;

vector<int> add_fac(const vector<int> &cur_fac, int x) {
  vector<int> res(5);
  if (cur_fac[4] == 1) return cur_fac;
  if (x == 0) {
    res[4] = 1;
    return res;
  }
  for (int i = 0; i < 4; i++) {
    int j = prime[i], cnt = 0;
    while (x % j == 0) { 
      x /= j;
      cnt++;
    }
    res[i] = min(fac[i], cur_fac[i] + cnt);
  }
  return res;
}

int dfs(int pos, vector<int> cur_fac, bool lim, bool lead, const vector<int> &num) {
  if (pos == -1) return cur_fac[4] == 1 || cur_fac == fac;
  if (!lim && !lead && dp.find(mkp(pos, cur_fac)) != dp.end()) return dp[mkp(pos, cur_fac)];
  int ub = (lim ? num[pos] : 9);
  int res = 0;
  if (lead) res = (res + dfs(pos - 1, cur_fac, 0, 1, num)) % mod;
  for (int i = lead; i <= ub; i++) {
    auto nxt = add_fac(cur_fac, i);
    res = (res + dfs(pos - 1, nxt, lim && i == ub, 0, num)) % mod;
  }
  if (!lim && !lead) dp[mkp(pos, cur_fac)] = res;
  //test(pos, cur_fac[0], res);
  return res;
}

int cal(__int128 x) {
  vector<int> num;
  int dig_cnt = 0;
  while (x) {
    num.eb(x % 10); x /= 10;
    dig_cnt++;
  }
  test(dig_cnt);
  vector<int> cur_fac(5);
  return dfs(dig_cnt - 1, cur_fac, 1, 1, num);
}

void get_allstates(int pos, vector<int> cur = {}) {
  if (pos == 4) {
    states.eb(cur);
    return;
  }
  for (int i = 0; i <= fac[pos]; i++) {
    cur.eb(i);
    get_allstates(pos + 1, cur);
    cur.pop_back();
  }
}

inline void solve() {
  int k;
  cin >> k;
  string sl, sr;
  cin >> sl >> sr;

  fac.resize(5, 0);
  int pk = k;
  for (int i = 0; i < 4; i++) {
    int j = prime[i];
    while (k % j == 0) {
      k /= j;
      fac[i]++;
    }
  }
  if (fac[0] + fac[1] + fac[2] + fac[3] == 0) {
    fac[4] = -1;
  } else {
    fac[4] = 0;
  }

  test(fac[0], fac[1], fac[2], fac[3]);
  //get_allstates(0);
  //test(SZ(states));
  __int128 l = 0, r = 0; 
  for (int i = 0; i < SZ(sl); i++) 
    l = l * 10 + (sl[i] - '0');
  for (int i = 0; i < SZ(sr); i++) 
    r = r * 10 + (sr[i] - '0');

  //int lll = l, rrr = r;
  //test(lll, rrr);
  if (pk == 1) {
    ll ans = (r - l + 1);
    cout << ans << '\n';
  } else {
    cout << (cal(r) - cal(l - 1) + 2 * mod) % mod;
  }
  //test(cal(r));
  //test(cal(l - 1));
}

signed main() {
	IO;	
  solve();
}
