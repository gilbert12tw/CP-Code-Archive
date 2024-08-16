#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
//#define loli
using namespace std;
typedef long long ll;
//#define int ll
#define pii pair<int, int>
#define fi first
#define se second
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

struct SplayTree {
  struct Node {
    int ch[2] = {0, 0}, p = 0;
    long long self = 0, path = 0;        // Path aggregates
    long long sub = 0, vir = 0;          // Subtree aggregates
    bool flip = 0;                       // Lazy tags
  };
  vector<Node> T;
  SplayTree(int n) : T(n + 1) {}
  void push(int x) {
    if (!x || !T[x].flip) return;
    int l = T[x].ch[0], r = T[x].ch[1];
    T[l].flip ^= 1, T[r].flip ^= 1;
    swap(T[x].ch[0], T[x].ch[1]);
    T[x].flip = 0;
  }
  void pull(int x) {
    int l = T[x].ch[0], r = T[x].ch[1]; push(l); push(r);
    T[x].path = T[l].path + T[x].self + T[r].path;
    T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
  }
  void set(int x, int d, int y) {
    T[x].ch[d] = y; T[y].p = x; pull(x);
  }
  void splay(int x) {
    auto dir = [&](int x) {
      int p = T[x].p; if (!p) return -1;
      return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
    };
    auto rotate = [&](int x) {
      int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
      set(y, dx, T[x].ch[!dx]);
      set(x, !dx, y);
      if (~dy) set(z, dy, x);
      T[x].p = z;
    };
    for (push(x); ~dir(x); ) {
      int y = T[x].p, z = T[y].p;
      push(z); push(y); push(x);
      int dx = dir(x), dy = dir(y);
      if (~dy) rotate(dx != dy ? x : y);
      rotate(x);
    }
  }
};

struct LinkCut : SplayTree {
  LinkCut(int n) : SplayTree(n) {}
  int access(int x) {
    int u = x, v = 0;
    for (; u; v = u, u = T[u].p) {
      splay(u);
      int& ov = T[u].ch[1];
      T[u].vir += T[ov].sub;
      T[u].vir -= T[v].sub;
      ov = v; pull(u);
    }
    return splay(x), v;
  }
  void reroot(int x) {
    access(x); T[x].flip ^= 1; push(x);
  }
  void Link(int u, int v) {
    reroot(u); access(v);
    T[v].vir += T[u].sub;
    T[u].p = v; pull(v);
  }
  void Cut(int u, int v) {
    reroot(u); access(v);
    T[v].ch[0] = T[u].p = 0; pull(v);
  }
  // Rooted tree LCA. Returns 0 if u and v arent connected.
  int LCA(int u, int v) {
    if (u == v) return u;
    access(u); int ret = access(v);
    return T[u].p ? ret : 0;
  }
  // Query subtree of u where v is outside the subtree.
  long long Subtree(int u, int v) {
    reroot(v); access(u); return T[u].vir + T[u].self;
  }
  // Query path [u..v]
  long long Path(int u, int v) {
    reroot(u); access(v); return T[v].path;
  }
  // Find root on original tree
  int Find(int x) {
      access(x); splay(x);
      while (T[x].ch[0]) 
          x = T[x].ch[0], push(x);
      splay(x);
      return x;
  }
  // Update vertex u with value v
  void Update(int u, long long v) {
    access(u); T[u].self = v; pull(u);
  }
};

// lazytag segment tree
struct SegmentTree {
    int n;
    vector<ll> seg, tag;
    SegmentTree(int _n): n(_n), seg(_n * 4), tag(_n * 4) {}
#define ls x<<1
#define rs (x<<1)|1
#define mid ((l+r)>>1)
    inline void up(int x) {
        seg[x] = seg[ls] + seg[rs];
    }

    inline void push_tag(int l, int r, int x, int v) {
        tag[x] += v;	
        seg[x] += v * (r - l + 1);
    }

    inline void down(int l, int r, int x) {
        if(!tag[x]) return;
        push_tag(l, mid, ls, tag[x]);
        push_tag(mid+1, r, rs, tag[x]);
        tag[x] = 0;
    }

    void modify(int a, int b, int v, int l, int r, int x) {
        if(a <= l and r <= b) {
            push_tag(l, r, x, v);
            return;
        }
        if (l != r) down(l, r, x);
        if(a <= mid) modify(a, b, v, l, mid, ls);
        if(b > mid) modify(a, b, v, mid+1, r, rs);
        up(x);
    }

    ll query(int a, int b, int l, int r, int x) {
        if (l != r) down(l, r, x);
        if(a <= l and r <= b) return seg[x];
        ll res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res += query(a, b, mid+1, r, rs);
        return res;
    }
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<pii> edge;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        edge.eb(u, v);
    }

    LinkCut lct(n);
    vector<int> mx_r(m, 0);
    int j = 0;
    for (int i = 0; i < m; i++) {
        j = max(j, i);
        while (j < m) {
            //if (lct.LCA(edge[j].fi, edge[j].se) != 0)
                //break;
            test(lct.Find(edge[j].fi));
            if (lct.Find(edge[j].fi) == lct.Find(edge[j].se))
                break;
            lct.Link(edge[j].fi, edge[j].se);
            j++;
        }
        mx_r[i] = j - 1;
        lct.Cut(edge[i].fi, edge[i].se);
    }

    int q; cin >> q;
    vector<vector<pii>> qry(m, vector<pii>());
    vector<ll> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        qry[l].eb(r, i);
    }

    SegmentTree seg(m);
    for (int l = m - 1; l >= 0; l--) {
        seg.modify(l, mx_r[l], 1, 0, m-1, 1);
        for (auto [r, id] : qry[l]) {
            ans[id] = seg.query(l, r, 0, m-1, 1);
        }
    }
    for (ll i : ans) cout << i << '\n';
}

signed main() {
    IO;	
    solve();	
}
