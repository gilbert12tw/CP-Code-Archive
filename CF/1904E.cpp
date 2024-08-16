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
#define inf 500000
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
    int res = -inf;
    if(a <= mid) res = query(a, b, l, mid, ls);
    if(b > mid) res = max(res, query(a, b, mid+1, r, rs));
    return res;
  }
  int query(int a, int b) { return query(a, b, 0, n, 1); }
};

const int mxN = 2e5 + 5;
int n, q;
vector<int> g[mxN];

vector<int> del[mxN];
vector<int> qry[mxN];

// LCA binary jump
int up[mxN][25], dep[mxN];
const int mxL = 20;
void dfs(int u, int p = -1) {
	if (p != -1) up[u][0] = p;
	for (int i = 1; (1<<i) <= dep[u]; i++) {
		up[u][i] = up[up[u][i-1]][i-1];
	}
	for (int v : g[u]) {
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

vector<int> dep_dfn;
int in[mxN], out[mxN], tk;
void dfs_tour(int u, int p) {
    in[u] = ++tk;
    dep_dfn.eb(dep[u]);
    for (int v : g[u]) {
        if (v != p) 
            dfs_tour(v, u);
    }
    out[u] = tk;
}

inline int jump(int x, int k) {
    for (int i = mxL; i >= 0; i--) {
        if (get_bit(k, i))
            x = up[x][i];
    }
    return x;
}

int ans[mxN];
void dfs_root(int u, int p, SegmentTree &seg) {
    // deal with query
    for (int id : qry[u]) {
        int highest = -1;
        for (int a : del[id]) {
            if (in[a] <= in[u] && in[u] <= out[a]) {
                highest = max(dep[a], highest); 
            } else {
                seg.modify(in[a], out[a], -inf);
            }
        }
        int hi_node = -1;

        if (highest != -1) {
            test(dep[u] - highest - 1);
            hi_node = jump(u, dep[u] - highest - 1);
            test(u, hi_node);
            ans[id] = seg.query(in[hi_node], out[hi_node]);
        } else {
            ans[id] = seg.query(1, n);
        }

        // Undo
        for (int a : del[id]) {
            if (in[a] > in[u] || in[u] > out[a]) {
                seg.modify(in[a], out[a], inf);
            }
        }
    }

    for (int v : g[u]) {
        if (v == p) continue;
        seg.modify(1, n, 1);
        seg.modify(in[v], out[v], -2);
        dfs_root(v, u, seg);
        seg.modify(in[v], out[v], 2);
        seg.modify(1, n, -1);
    } 
}

inline void solve() {
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].eb(b); g[b].eb(a);
    }
    
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        qry[x].eb(i);
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int a; cin >> a;
            del[i].eb(a);
        }
    }

    dfs(1, -1);
    dep_dfn.eb(-inf - inf);
    dfs_tour(1, -1);

    SegmentTree seg(n);
    seg.build(dep_dfn);

    dfs_root(1, -1, seg);
    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
}

signed main() {
	IO;	
	solve();	
}
