#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<map>
#include<bitset>
#include<cmath>
#include<numeric>
#include<random>
#define loli
using namespace std;
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
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

using LL = long long;

LL modMul(LL a, LL b, LL m) { return __int128{a} * b % m; }

LL pow(LL a, LL b, LL m) {
  LL ret = 1;
  for (; b; a = modMul(a, a, m), b >>= 1)
    if (b % 2)
      ret = modMul(ret, a, m);
  return ret;
}

LL sprp[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool isPrime(LL n) {
  if (n == 2)
    return true;
  if (n < 2 || n % 2 == 0)
    return false;
  LL t = 0, u = n - 1;
  for (; u % 2 == 0; t++)
    u >>= 1;
  for (int i = 0; i < 7; i++) {
    LL a = sprp[i] % n;
    if (a == 0 || a == 1 || a == n - 1)
      continue;
    LL x = pow(a, u, n);
    if (x == 1 || x == n - 1)
      continue;
    for (int j = 1; j < t; j++) {
      x = modMul(x, x, n);
      if (x == 1)
        return false;
      if (x == n - 1)
        break;
    }
    if (x == n - 1)
      continue;
    return false;
  }
  return true;
}

inline LL f(LL x, LL m) { return (modMul(x, x, m) + 1) % m; }

inline LL pollard_rho(LL n) {
  if (!(n & 1))
    return 2;
  while (true) {
    LL y = 2, x = rand() % (n - 1) + 1, res = 1;
    for (int sz = 2; res == 1; sz *= 2) {
      for (int i = 0; i < sz && res <= 1; i++) {
        x = f(x, n);
        res = gcd(abs(x - y), n);
      }
      y = x;
    }
    if (res != 0 && res != n)
      return res;
  }
}

void factorize(LL n, vector<LL> &ans) {
  if (isPrime(n))
    ans.eb(n);
  else {
    auto p = pollard_rho(n);
    factorize(p, ans);
    factorize(n / p, ans);
  }
}

LL fac(LL n) {
    if (n == 1) return 0;
    if (isPrime(n)) return n;

    LL p = pollard_rho(n);
    return max(fac(p), fac(n / p));
}

inline void solve() {
    srand((unsigned)time(NULL));

    LL n;
    cin >> n;

    if (isPrime(n)) {
        cout << "Prime\n";
    } else {
        cout << fac(n) << '\n';
    }

}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
