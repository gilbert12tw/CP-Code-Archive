#include<bits/stdc++.h>
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
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

int n, m;

#define llu unsigned long long
inline llu add(llu a, llu b, llu c) { return (__int128{a} + b) % c; }
inline llu mul(llu a, llu b, llu c) { return __int128{a} * b % c; }
inline llu mpow(llu a, llu b, llu c) {
  llu res = 1;
  while (b) {
    if (b & 1) res = mul(res, a, c);
    a = mul(a, a, c) ; b>>=1;
  }
  return res;
}
inline bool isprime(llu x) {
  static auto witn = [](llu a, llu n, int t) {
    if (!a) return false;
    while (t--) {
      llu a2 = mul(a, a, n);
      if (a2 == 1 && a != 1 && a != n - 1) return true;
      a = a2;
    }
    return a != 1;
  };
  if (x < 2) return false;
  if (!(x & 1)) return x == 2;
  int t = __builtin_ctzll(x - 1);
  llu odd = (x - 1) >> t;
  for (llu m:
    {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
    if (witn(mpow(m % x, odd, x), x, t))
      return false;
  return true;
}


// does not work when n is prime
// return any non-trivial factor
inline llu f(llu x, llu m) { return (mul(x, x, m) + 1) % m; }
inline llu pollard_rho(llu n) {// don't input 1
  if (!(n & 1)) return 2;
  while (true) {
    llu y = 2, x = rand() % (n - 1) + 1, res = 1;
    for (int sz = 2; res == 1; sz *= 2) {
      for (int i = 0; i < sz && res <= 1; i++) {
        x = f(x, n);
        res = __gcd(x - y >= 0 ? x - y : y - x, n);
      }
      y = x;
    }
    if (res != 0 && res != n) return res;
  }
}
void fac(llu x, vector<llu> &ans) {
  if (isprime(x)) ans.emplace_back(x);
  else {
    llu p = pollard_rho(x);
    fac(x / p, ans); fac(p, ans);
  }
}

inline void madd(int &a, const int &b) {
    a += b;
    if (a >= mod) a -= mod;
}

inline void solve() {
    cin >> n >> m;

    if (m == 1) {
        int x = 0;
        for (int i = 0; i < n; i++) {
            int y; cin >> y;
            x += (y == 1);
        }
        cout << mpow(2, x, mod) - 1 << '\n';
        return;
    }

    vector<llu> fact;
    if (m != 1) fac(m, fact);
    map<int, int> mp;
    for (int i : fact) {
        mp[i]++;
    }

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        int msk = 0, id_cnt = 0;
        for (auto [x, up] : mp) {
            int cnt = 0;
            while (y % x == 0) {
                y /= x;
                cnt++;
            }
            if (cnt > up) {
                msk = -1;
                break;
            }
            if (cnt == up) {
                msk |= (1LL<<id_cnt);
            }
            id_cnt++;
        }
        if (msk != -1 && y == 1) a.eb(msk);
    }

    int bsz = SZ(mp);
    vector<int> dp(1<<bsz);
    dp[0] = 1;
    for (int j : a) {
        for (int i = (1<<bsz) - 1; i >= 0; i--) {
            if (!dp[i]) continue;
            madd(dp[i | j], dp[i]);
        }
    }
    cout << dp[(1<<bsz) - 1] << '\n';
}

signed main() {
	IO;	
	solve();	
}
