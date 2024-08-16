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

const int mxN = 1e5 + 5;
struct BIT{
  int b[mxN], n;
  BIT(int _n) {
    n = _n;
    for (int i = 0; i <= n; i++) b[i] = 0;
  }
  void build(int a[]) {
    for (int i = 1; i <= n; i++) {
      b[i] += a[i];
      int j = i + (i&-i);
      if (j <= n) b[j] += b[i];
    }
  }
  int qry(int i) {
    int res = 0;
    for (; i > 0; i -= (i&-i)) res += b[i];
    return res;
  }
  void upd(int i, int v) {
    for (; i <= n; i += (i&-i)) b[i] += v; 
  }
};

inline void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &i : a) cin >> i;
  BIT bit0(1e5), bit1(1e5);
  vector<int> pre(n), suf(n);
  for (int i = 0; i < n; i++) {
    int res = i - bit0.qry(a[i]);
    pre[i] = res;
    bit0.upd(a[i], 1);
  }

  for (int i = n - 1; i >= 0; i--) {
    int res = (n - i - 1) - bit1.qry(a[i]);
    suf[i] = res;
    bit1.upd(a[i], 1);
  }

  map<int, vector<int>> mp;
  for (int i = 0; i < n; i++) mp[a[i]].eb(i);

  int ans = 0;
  for (auto [x, v] : mp) {
    int m = SZ(v);
    vector<int> costpre(m), costsuf(m);
    costpre[0] = pre[v[0]];
    for (int i = 1; i < m; i++) {
      costpre[i] = costpre[i-1] + pre[v[i]];
    }
    costsuf[m-1] = suf[v[m-1]];
    for (int i = m - 2; i >= 0; i--) {
      costsuf[i] = costsuf[i+1] + suf[v[i]];
    }
    int mn = min(costpre[m-1], costsuf[0]);
    for (int i = 0; i < m - 1; i++) {
      mn = min(mn, costpre[i] + costsuf[i+1]);
    }
    ans += mn;
  }
  cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
