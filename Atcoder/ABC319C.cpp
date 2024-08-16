#include<bits/stdc++.h>
#include<iomanip>
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

int c[3][3];
int a[3][3];

bool check() {
  for (int i = 0; i < 3; i++) {
    if ((c[i][0] == c[i][1] && c[i][2] < 0) || (c[i][1] == c[i][2] && c[i][0] < 0)
      || (c[i][0] == c[i][2] && c[i][1] < 0)) {
      return 1;
    }
    if ((c[0][i] == c[1][i] && c[2][i] < 0) || (c[1][i] == c[2][i] && c[0][i] < 0) 
      || (c[0][i] == c[2][i] && c[1][i] < 0)) {
      return 1;
    }
  }
  if ((c[0][0] == c[1][1] && c[2][2] < 0) || 
      (c[1][1] == c[2][2] && c[0][0] < 0) || 
      (c[0][0] == c[2][2] && c[1][1] < 0) ) {
    return 1;
  }
  if ((c[2][0] == c[1][1] && c[0][2] < 0) || 
      (c[1][1] == c[0][2] && c[2][0] < 0) || 
      (c[2][0] == c[0][2] && c[1][1] < 0)) {
    return 1;
  }
  return 0;
}

inline void solve() {
  for (int i = 0; i < 3; i++) 
    for (int j = 0; j < 3; j++)
      cin >> a[i][j];

  int mx = 0, cnt = 0;
  vector<int> v;
  for (int i = 0; i < 9; i++) v.eb(i);
  do {
    mx++;
    int bad = 0;
    for (int i = 0; i < 9; i++) {
      int x = i / 3, y = i % 3;
      c[x][y] = -i - 10;
    }
    for (int i = 0; i < 9; i++) {
      int x = v[i] / 3, y = v[i] % 3;
      c[x][y] = a[x][y];
      if (check()) {
        bad = 1;
        break;
      }
    }
    if (bad) continue;
    cnt++;
  } while(next_permutation(ALL(v)));
  
  //test(cnt);
  double ans = (1.0 * cnt) / (1.0 * mx);
  
  cout << fixed << setprecision(10) << ans;
}

signed main() {
	IO;	
	solve();	
}
