#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
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

const int mxN = 5e5 + 5;
const int BSZ = 150;
int n, q;
ll a[mxN];
//int last_set_tm[mxN];
//int last_mod[mxN / BSZ][BSZ];
ll add_tag[mxN / BSZ + 1][BSZ][BSZ]; // add_tag[i][j] -> (mod i) = j
//int set_tag[mxN / BSZ][BSZ][BSZ];

inline int Bid(int x) { return (x / BSZ);}
inline int BR(int x) { return (x / BSZ + 1) * BSZ - 1;}
inline int BL(int x) { return (x / BSZ) * BSZ;}

void madd(int l, int r, int x, int v, int op_time) {
  if (x >= BSZ || (r - l + 1) / x <= BSZ) {
    for (int i = l; i <= r; i += x) 
      a[i] += v;
    return;
  }
  
  for (int i = l; i <= BR(l); i += x) a[i] += v;
  for (int i = r; i >= BL(r); i -= x) a[i] += v;

  for (int i = Bid(l) + 1; i < Bid(r); i++) {
    add_tag[i][x][l % x] += v;
  }
}

void mset(int l, int r, int x, int v, int op_time) {
  /*
  if (x >= BSZ || (r - l + 1) <= BSZ) {
    for (int i = l; i <= r; i += x) {
      a[i] = v;
      last_set_tm[i] = op_time;
    }
    return;
  }
  */
}

ll query(int x) {
  ll res = a[x];
  for (int i = 1; i < BSZ; i++) {
    res += add_tag[Bid(x)][i][x % i];
  }
  return res;
}

inline void solve() {
  cin >> n >> q;
  for (int i = 0; i < q; i++) {
    int op; cin >> op;
    int l, r, x, y, v;
    if (op == 3) {
      cin >> y; y--;
      cout << query(y) << '\n';
    } else {
      cin >> l >> r >> x >> v;
      l--; r--;
      madd(l, r, x, v, i);
    }
  }
}

signed main() {
  IO;	
  solve();	
}
