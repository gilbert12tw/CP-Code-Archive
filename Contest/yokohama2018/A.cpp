#include<bits/stdc++.h>
//#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define fi first
#define se second
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

vector<pii> decod(string &s) {
  vector<pii> res;
  int num = 0;
  for (int i = 0; i < SZ(s); i++) {
    if (isdigit(s[i])) {
      num = (s[i] - '0');
      while (i + 1 < SZ(s) && isdigit(s[i+1])) {
        num = num * 10 + (s[++i] - '0');
      }
      res.eb(-1, num);
    } else {
      res.eb((int)(s[i]), 0);
    }
  }
  return res;
}

bool cmp(vector<pii> &a, vector<pii> &b) {
  for (int i = 0; i < SZ(a) && i < SZ(b); i++) {
    if (a[i] < b[i]) return 1;
    if (a[i] > b[i]) return 0;
  }
  if (SZ(a) >= SZ(b)) return 0;
  return 1;
}

inline void solve() {
  int n; cin >> n;
  string s0; cin >> s0;
  vector<pii> ds0, ds;

  ds0 = decod(s0);

  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    ds = decod(s);

    if (cmp(ds, ds0)) cout << "-\n";
    else cout << "+\n";
  }
}

signed main() {
	IO;	
	solve();	
}
