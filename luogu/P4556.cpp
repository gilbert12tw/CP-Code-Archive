#include<bits/stdc++.h>
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

const int mxN = 1e5 + 5;
// dynamic lazytag segment tree
struct SegmentTree {
    int n, tot, root;
    vector<int> seg, ls, rs;
    SegmentTree(int _n = 0): n(_n), tot(0), root(0), seg(_n * 50), ls(_n * 50), rs(_n * 50) {}

    inline int op(const int &a, const int &b) {
        return max(a, b);
    }

    inline void up(int x) {
        seg[x] = op(seg[ls[x]], seg[rs[x]]);
    }

    void modify(int pos, int val, int l, int r, int &idx) {
        if (idx == 0) idx = ++tot;
        if (l == r) {
            seg[idx] += val;
            return;
        }
        int mid = (l+r)>>1;
        if (pos <= mid) modify(pos, val, l, mid, ls[idx]);
        else modify(pos, val, mid+1, r, rs[idx]);
        up(idx);
    }
    void modify(int &idx, int pos, int val) { modify(pos, val, 1, n, idx); }

    int merge(int p, int q, int l, int r) {
        if (!p || !q) return (p | q);
        if (l == r) {
            seg[p] += seg[q];
            return p;
        }
        int mid = (l+r)>>1;
        ls[p] = merge(ls[p], ls[q], l, mid);
        rs[p] = merge(rs[p], rs[q], mid+1, r);
        up(p);
        return p;
    }
    int merge(int p, int q) { return merge(p, q, 1, n); }

    int search(int idx, int l, int r) {
        if (!idx) return 0;
        if (l == r) { 
            if (seg[idx] == 0) return 0;
            return l;
        }
        int mid = (l+r)>>1;
        if (ls[idx] && (rs[idx] == 0 || seg[ls[idx]] >= seg[rs[idx]])) {
            return search(ls[idx], l, mid);
        }
        return search(rs[idx], mid+1, r);
    }
    int search(int idx) { return search(idx, 1, n); }
};

SegmentTree seg_tree(mxN);

int root[mxN];
// LCA
const int lgN = 20;
int timer;
int in[mxN], out[mxN], dep[mxN], fa[lgN][mxN];
vector<int> tree[mxN];
void dfs(int u = 1, int p = 1) {
    in[u] = ++timer;
    fa[0][u] = p;
    for (int i = 1; i < lgN; i++) 
        fa[i][u] = fa[i-1][fa[i-1][u]];
    for (int v : tree[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
    out[u] = timer;
}

bool ancestor(int u, int v){
    return in[u] <= in[v] && out[u] >= out[v];
}
 
int lca(int u, int v){
    if(ancestor(u, v))  return u;
    if(ancestor(v, u))  return v;
    for(int i = lgN - 1; i >= 0; i--)
        if(!ancestor(fa[i][u], v))
            u = fa[i][u];
    return fa[0][u];
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].eb(v);
        tree[v].eb(u);
    }

    dfs();
    
    for (int i = 0; i < m; i++) {
        int a, b, z;
        cin >> a >> b >> z;
        int lc = lca(a, b);
        assert(lc != 0);
        seg_tree.modify(root[a], z, 1);
        seg_tree.modify(root[b], z, 1);
        seg_tree.modify(root[lc], z, -1);
        if (lc != 1) seg_tree.modify(root[fa[0][lc]], z, -1);
    }

    vector<int> ans(n + 1);
    auto dfs_sum = [&](int u, int p, auto&& dfs_sum) -> void {
        for (int v : tree[u]) {
            if (v == p) continue;
            dfs_sum(v, u, dfs_sum);
            seg_tree.merge(root[u], root[v]);
        }
        ans[u] = seg_tree.search(root[u]);
    };
    dfs_sum(1, 0, dfs_sum);
    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}

signed main() {
	IO;	
	solve();	
}
