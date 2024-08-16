#include<bits/stdc++.h>
//#define loli
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

const int mxN = 4e5 + 5;

int n, m;
int val[mxN];
vector<int> g[mxN];

// Centriod Decomposition
int pa[mxN], sz[mxN];
vector<int> dis_to_pa[mxN];
bitset<mxN> del;

void get_sz(int u, int p) {
	sz[u] = 1;
	for (int v : g[u]) {
		if (v == p or del[v]) continue;
		get_sz(v, u);
		sz[u] += sz[v];	
	}
}

int get_centroid(int u, int n, int p) {
	for (int v : g[u]) {
		if (v != p and !del[v] and sz[v] * 2 > n) 
			return get_centroid(v, n, u);
	}
	return u;
}

void get_dis(int u, int p, int dis = 0) {
    if (p != 0) dis_to_pa[u].eb(dis);
    for (int v : g[u]) {
        if (v == p || del[v]) continue;
        get_dis(v, u, dis + 1);
    } 
}

int build(int u) {
	get_sz(u, -1);	
	int centroid = get_centroid(u, sz[u], -1);
    get_dis(centroid, 0, 0);
	del[centroid] = 1;
	for (int v : g[centroid]) {
		if (del[v]) continue;
		pa[build(v)] = centroid;
	}
	return centroid;
}

// Segment Tree
struct SegmentTree {
    struct Segment {
        int ls = 0, rs = 0, val = 0;
    } seg[mxN * 20];
    int tot = 0;
    int root[mxN];
    
    void modify(int &id, int pos, int v, int l = 0, int r = n - 1) {
        if (!id) id = ++tot; 
        seg[id].val += v;
        if (l == r) return;
        int mid = (l+r) >> 1;
        if (pos <= mid) modify(seg[id].ls, pos, v, l, mid);
        else modify(seg[id].rs, pos, v, mid+1, r);
    }

    int query(int id, int a, int b, int l = 0, int r = n - 1) {
        if (b < a) return 0;
        if (!id) return 0;
        if (a <= l && r <= b) return seg[id].val;
        int res = 0, mid = (l+r) >> 1;
        if (a <= mid) res += query(seg[id].ls, a, b, l, mid);
        if (b > mid)  res += query(seg[id].rs, a, b, mid+1, r);
        return res;
    }
} segtree, segtree2;

void modify(int x, int v) {
    int cur = x;
    
    segtree.modify(segtree.root[cur], 0, v);
    for (int dis : dis_to_pa[x]) {
        cur = pa[cur]; 
        if (!cur) break;
        segtree.modify(segtree.root[cur], dis, v);
    }
}

int qry(int x, int k) {
    int cur = x, prv = x, res = 0;
    res += segtree.query(segtree.root[cur], 0, k);
    for (int dis : dis_to_pa[x]) {
        prv = cur;
        cur = pa[cur];
        if (dis > k) break;
        res += segtree.query(segtree.root[cur], 0, k - dis)
               - segtree.query(segtree.root[prv], 0, k - dis * 2);
    }
    return res;
}

inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        cin >> val[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }

    // CD
    build(1);

    for (int i = 1; i <= n; i++) reverse(ALL(dis_to_pa[i]));

    for (int u = 1; u <= n; u++) {
        modify(u, val[u]);
    }

    int lastans = 0;
    while (m--) {
        int opt, x, k;
        cin >> opt >> x >> k;
        x ^= lastans; k ^= lastans;
        if (opt == 0) {
            lastans = qry(x, k);
            cout << lastans << '\n';
        }
        else {
            modify(x, k - val[x]);
            val[x] = k;
        }
    }
}

signed main() {
	IO;	
	solve();	
}
