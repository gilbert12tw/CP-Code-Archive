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
#define MOD 998244353
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

const int mxN = 3e5 + 5;
vector<int> g[mxN];
int a[mxN];

// lazytag segment tree
struct SegmentTree {
  int n;
  vector<int> seg, tag;

  SegmentTree(int _n): n(_n), seg(_n * 4), tag(_n * 4) {}

#define ls x<<1
#define rs (x<<1)|1
#define mid ((l+r)>>1)

  inline void up(int x) {
    seg[x] = max(seg[ls], seg[rs]);
  }

  inline void push_tag(int l, int r, int x, int v) {
    tag[x] += v;	
    seg[x] += v;
  }

  inline void down(int l, int r, int x) {
    if(!tag[x]) return;
    push_tag(l, mid, ls, tag[x]);
    push_tag(mid+1, r, rs, tag[x]);
    tag[x] = 0;
  }
  void build(vector<int> &a, int l, int r, int x = 1) {
    if(l == r) {
      seg[x] = a[l];
      return;
    }
    build(a, l, mid, ls);	build(a, mid+1, r, rs);
    up(x);
  } 
  void build(vector<int> &a) { build(a, 0, n, 1); }

  void modify(int a, int b, int v, int l, int r, int x = 1) {
    if(a <= l and r <= b) {
      push_tag(l, r, x, v);
      return;
    }
    if (l != r) down(l, r, x);
    if(a <= mid) modify(a, b, v, l, mid, ls);
    if(b > mid) modify(a, b, v, mid+1, r, rs);
    up(x);
  }
  void modify(int a, int b, int v) { modify(a, b, v, 0, n, 1); }

  int query(int a, int b, int l, int r, int x = 1) {
    if (l != r) down(l, r, x);
    if(a <= l and r <= b) return seg[x];
    int res = 0;
    if(a <= mid) res = query(a, b, l, mid, ls);
    if(b > mid) res = max(res, query(a, b, mid+1, r, rs));
    return res;
  }
  int query(int a, int b) { return query(a, b, 0, n, 1); }
};

int tp;
int st[mxN], ed[mxN];
void dfs(int u, int p) {
    st[u] = ++tp;
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    ed[u] = tp;
}

set<pii> color[mxN];
int ans = 1;
void cal(int u, int p, SegmentTree &seg) {
    for (int v : g[u]) {
        if (v == p) continue;
        cal(v, u, seg);
    }
    int mx = 1, mx2 = 0;
    // update a[u]
    auto it = color[a[u]].lower_bound(mkp(st[u], 0));
    while (it != color[a[u]].end() && it->second <= ed[u]) {
        seg.modify(it->first, it->second, -1);
        it = color[a[u]].erase(it);
    }
    seg.modify(st[u], ed[u], 1);
    color[a[u]].insert(mkp(st[u], ed[u]));

    for (int v : g[u]) {
        int res = seg.query(st[v], ed[v]);
        if (res > mx) {
            mx2 = mx;
            mx = res;
        } else {
            mx2 = max(mx2, res);
        }
    }
    ans = max(ans, mx * mx2);
    test(u, mx, mx2);
}

inline void solve() {
    int n; cin >> n;
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        g[x].eb(i);
    }
    for (int i = 1; i <= n; i++) cin >> a[i];
    SegmentTree seg(n);
    ans = 1;
    dfs(1, 0);
    cal(1, 0, seg);
    cout << ans << '\n';

    for (int i = 0; i <= n; i++) {
        g[i].clear();
        color[i].clear();
    }
    tp = 0;
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
