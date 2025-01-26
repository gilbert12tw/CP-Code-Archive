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
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
  cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

struct BIT{
  vector<int> b;
  int n;
  BIT(int _n): b(_n + 1), n(_n) {}
  int qry(int i) {
    int res = 0;
    i += 1;
    if (i == 0) return 0;
    for (; i > 0; i -= (i&-i)) res += b[i];
    return res;
  }
  void upd(int i, int v) {
    i += 1;
    if (i == 0) return;
    for (; i <= n; i += (i&-i)) b[i] += v; 
  }
};

inline void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> x(n), h(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> h[i];
  }

  vector<vector<pii>> qry(n);
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    l--, r--;
    qry[r].eb(l, i);
  }

  BIT bit(n + 1);
  vector<int> stk, ans(q), nxt(n);
  set<pii> st;
  for (int i = 0; i < n; i++) {
    int lst = x[0], is_cut = 0;
    if (!stk.empty()) lst = x[stk.back()];
    // go right
    if (i != n - 1 && x[i] + h[i] <= x[i + 1]) {
      bit.upd(i, 1);
      is_cut = 1;
    }
    // go left (with dependency)
    if (!is_cut && x[i] - h[i] >= lst) {
      bit.upd(i, 1);
      is_cut = 1;

      auto it = st.lower_bound(mkp(x[i] - h[i], inf));
      while (it != st.end() && it->first < x[i]) {
        nxt[it->second] = i;
        it = st.erase(it);
      }
    }

    if (!is_cut) stk.eb(i);
    else {
      while (!stk.empty()) {
        if (x[stk.back()] + h[i] <= x[i + 1]) {
          bit.upd(stk.back(), 1);
          stk.pop_back();
        }
      }
    }

    for (auto [l, id] : qry[i]) {
      ans[id] = bit.qry(i) - bit.qry(l - 1);
      int u = l - 1;
      if (u >= 0) u = nxt[u];
      else u = 0;
      while (u) {
        ans[id]--;
        u = nxt[u];
      }
    }
    st.insert(mkp(x[i], i));
  }
  for (int i : ans) cout << i << '\n';
}

signed main() {
  IO;	
  solve();	
}
