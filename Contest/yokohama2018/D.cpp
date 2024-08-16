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
#define mod 1000000007
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

inline void solve() {
  string a, b;
  cin >> a >> b;
  int n = SZ(a), m = SZ(b);
  vector<vector<int>> nxta(n, vector<int>(2)), nxtb(m, vector<int>(2));
  int one = n, zero = n;
  for (int i = n - 1; i >= 0; i--) {
    nxta[i][0] = zero;
    nxta[i][1] = one;
    if (a[i] == '0') zero = i;
    else one = i;
  }
  int oneb = m, zerob = m;
  for (int i = m - 1; i >= 0; i--) {
    nxtb[i][0] = zerob;
    nxtb[i][1] = oneb;
    if (b[i] == '0') zerob = i;
    else oneb = i;
    test(nxtb[i][0], nxtb[i][1]);
  }
  test(zero, zerob, one, oneb);


  // bfs
  queue<pair<pii, string>> q;
  q.push(mkp(zero, zerob), "0");
  q.push(mkp(one, oneb), "1");

  vector<vector<int>> vis(n + 1, vector<int>(m + 1));
  vis[zero][zerob] = vis[one][oneb] = 1;

  while (!q.empty()) {
    auto p = q.front(); q.pop();
    test(p.F.F, p.F.S, p.S);
    if (p.F == mkp(n, m)) {
      cout << p.S << '\n';
      return;
    }
    // 0
    int u = p.F.F, v = p.F.S;
    int nxtu, nxtv;
    if (u != n) nxtu = nxta[u][0];
    else nxtu = n;
    if (v != m) nxtv = nxtb[v][0];
    else nxtv = m;

    if (!vis[nxtu][nxtv]) {
      vis[nxtu][nxtv] = 1;
      p.S.push_back('0');
      q.push(mkp(nxtu, nxtv), p.S);
      p.S.pop_back();
    }

    // 1
    if (u != n) nxtu = nxta[u][1];
    else nxtu = n;
    if (v != m) nxtv = nxtb[v][1];
    else nxtv = m;
    if (!vis[nxtu][nxtv]) {
      vis[nxtu][nxtv] = 1;
      p.S.push_back('1');
      q.push(mkp(nxtu, nxtv), p.S);
      p.S.pop_back();
    }
  }
}

signed main() {
	IO;	
	solve();	
}
