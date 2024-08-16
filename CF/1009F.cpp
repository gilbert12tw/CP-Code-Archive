#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
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

const int mxN = 1e6 + 5;

int n;
vector<int> g[mxN];

class Segment {
public:
    int mx;
    Segment *ls, *rs;
    Segment() {
        mx = 0;
        ls = rs = NULL;
    }
};

class SegmentTree {
private:
    Segment* root[mxN];

    // methods
    Segment* modify(int pos, int val, int l = 0, int r = n - 1) {
        Segment *cur = new Segment;
        cur->mx = val;
        if (l == r) return cur;
        int mid = ((l+r)>>1);
        if (pos <= mid) cur->ls = modify(pos, val, l, mid);
        else cur->rs = modify(pos, val, mid+1, r);
        return cur;
    }

    Segment* merge(Segment *u, Segment *v, int l = 0, int r = n - 1) {
        if (u == NULL) return v;
        if (v == NULL) return u;

        if (l == r) {
            u->mx += v->mx;
            delete v;
            return u;
        }

        int mid = ((l+r)>>1);
        u->ls = merge(u->ls, v->ls, l, mid);
        u->rs = merge(u->rs, v->rs, mid+1, r);

        // up 
        if (u->ls != NULL) u->mx = max(u->mx, u->ls->mx);
        if (u->rs != NULL) u->mx = max(u->mx, u->rs->mx);
        delete v;
        return u;
    }

    int findMax(Segment *u, int l = 0, int r = n - 1) {
        if (l == r) return l;
        int mid = ((l+r)>>1);
        if (u->ls and u->ls->mx == u->mx)
            return findMax(u->ls, l, mid);
        else 
            return findMax(u->rs, mid+1, r);
    }

public:
    void setTree(int u, int dep) {
        root[u] = modify(dep, 1);
    }

    void mergeTree(int u, int v) {
        // remind that it minds that order of u, v
        root[u] = merge(root[u], root[v]);
    }

    int getAns(int u) {
        return findMax(root[u]);
    }
} segtree;

int ans[mxN];

void dfs(int u, int p = 0, int dep = 0) {
    int first = 1;
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u, dep + 1);
        if (first) segtree.setTree(u, dep);
        first = 0;
        segtree.mergeTree(u, v);
    }
    if (first) segtree.setTree(u, dep);
    ans[u] = segtree.getAns(u) - dep;
}

inline void init() {
    // initialize global variable
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }
}

inline void solve() {
    init();

    dfs(1);

    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}

signed main() {
	IO;	
	solve();	
}
