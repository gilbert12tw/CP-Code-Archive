#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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
#define get_bit(x, y) ((x>>y)&1ULL)
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

int hibit(ull x) {
  int hi = 0;
  for (int i = 0; i < 63; i++) {
    if (get_bit(x, i)) hi = i;
  }
  return hi;
}

inline void solve() {
  ull n, k;
  cin >> n >> k;
  if (k == 1) {
    cout << 1 << '\n';
    return;
  }

  int hi = hibit(n);
  ull leaves = n - (1ULL<<hi) + 1;
  ull ans = 0;
  for (int i = 0; i <= hi; i++) {
    if (i == 0) {
      continue;
    }
    //if (i > k) break;
    ull subtree = (1ULL<<(hi-i+1)) - 1;
    ull seg = (1ULL<<(hi - i));

    // case 1 : full leaves
    ull num1 = leaves / seg;
    if (n - subtree >= k) 
      ans += num1;

    // case 2 : half 
    ull num2 = 0;
    if (leaves % seg) {
      num2 = 1;
      ull tmp = leaves % seg;
      ull cost = (1ULL<<(hi-i)) - 1 + tmp;
      if (n - cost >= k) ans += num2;
    }

    // case 3 : no leaf
    ull num3 = min(leaves, (1ULL<<i)) - num1 - num2;
    ull noleaf = (1ULL<<(hi-i)) - 1;
    if (n - noleaf >= k) ans += num3;
  }
  cout << ans;

}

signed main() {
	IO;	
	solve();	
}
