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
  int n; cin >> n;
  vector<int> a(n), d(n);
  vector<vector<pii>> seg(n);
  for (int &i : a) cin >> i;
  for (int &i : d) cin >> i;

  for (int i = 0; i < n; i++) {
    int l = max(0ll, i - d[i]);
    int r = min(n - 1, i + d[i]);
    if (a[i]) seg[l].eb(r, a[i]);
  }

  auto check = [&](int z) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    for (int i = 0; i < n; i++) {
      for (auto [r, val] : seg[i]) {
        pq.push(r, val);
      }

      int res = z; 
      while (!pq.empty() && res > 0) {
        auto [r, val] = pq.top(); pq.pop();
        if (r < i) return false;
        if (val > res) {
          pq.push(r, val - res);
          break;
        }
        res -= val;
      }
    }
    return pq.empty();
  };
  
  int l = 0, r = 1e10 + 10;
  while (l < r) {
    int mid = (l + r) / 2;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }
  cout << l;
}

signed main() {
	IO;	
	solve();	
}
