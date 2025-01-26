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

struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    int n;
    vector<int> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4) {}

    inline int op(const int &a, const int &b) {
        return max(a, b);
    }

    void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    void modify(int p, int v, int l, int r, int x) {
        if(l == r) {
            seg[x] = max(seg[x], v);
            return;
        }
        if(p <= mid) modify(p, v, l, mid, ls);
        else modify(p, v, mid+1, r, rs);
        up(x);
    }
    void modify(int p, int v) { modify(p, v, 0, n, 1); }

    int query(int a, int b, int l, int r, int x) {
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs));
        return res;
    }
    int query(int a, int b) { return query(a, b, 0, n , 1); }
};

inline void solve() {
  int n; cin >> n;
  vector<int> a(n);
  int mx = 0;
  for (int &i : a) { 
    cin >> i;
    mx = max(i, mx);
  }

  vector<vector<int>> div(100001);

  for (int i = 1; i <= mx; i++) {
    for (int j = i; j <= mx; j += i) {
      div[j].eb(i);
    }
  }
  for (int i = 1; i <= mx; i++) reverse(ALL(div[i]));

  vector<vector<pii>> lst(n);
  map<int, int> mp;
  for (int i = 0; i < n; i++) {
    for (int j : div[a[i]]) {
      if (mp.find(j) != mp.end()) {
        if (lst[i].empty() || lst[i].back().second < mp[j]) {
          lst[i].eb(j, mp[j]);
        }
      }
      mp[j] = i;
    }
  }

  int q; cin >> q;
  vector<vector<pii>> qry(n);
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    qry[r].eb(l, i);
  }

  Segment_Tree seg(n + 1);
  vector<int> ans(q);
  for (int i = 0; i < n; i++) {
    for (auto [val, pos] : lst[i]) {
      seg.modify(pos, val);
    }
    for (auto [l, idx] : qry[i]) {
      ans[idx] = seg.query(l, i);
    }
  }
  for (int i : ans) cout << i << '\n';
}

signed main() {
	IO;	
	solve();	
}
