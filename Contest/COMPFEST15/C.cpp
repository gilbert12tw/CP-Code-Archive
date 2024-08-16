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
#define mod 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 5e5 + 5;
int ans = 0;
int s[mxN];
vector<pii> g[mxN];

int dfn;
int vistm[mxN], out[mxN];
int res[mxN], cnt[2][mxN];
int ind[mxN];
int tot[2];

inline void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    g[i].resize(s[i]);
    for (int j = 0; j < s[i]; j++) {
      cin >> g[i][j].first >> g[i][j].second;
      ind[g[i][j].first]++;
    }
  }
  
  queue<int> q;
  q.push(1);

  while (!q.empty()) {
    int u = q.front(); q.pop();
    test(u, cnt[0][u], cnt[1][u]);
    for (auto [v, w] : g[u]) {

      cnt[0][v] = (cnt[0][v] + cnt[0][u]) % mod;
      cnt[1][v] = (cnt[1][v] + cnt[1][u]) % mod;

      if (!w) ans = (ans + tot[1] - cnt[1][v]) % mod;
      cnt[w][v] = (cnt[w][v] + 1) % mod;

      tot[w]++;
      ind[v]--;
      if (ind[v] == 0) q.push(v);
    }
  }

  cout << ans;
}

signed main() {
	IO;	
	solve();	
}
