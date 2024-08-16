#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
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

const int mxN = 6e5 + 5;

struct DSU {
	vector<int> dsu, sz;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
	void oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return; 
		dsu[a] = b;
		sz[b] += sz[a];
	}
};

int pw[mxN];
vector<int> tr[mxN];

int build_kruskal(vector<array<int, 3>> &edge) {
    sort(ALL(edge), [](auto a, auto b) {
        return a[2] < b[2];
    });
    int n = SZ(edge) + 1, id_cnt = n + 1;
    DSU dsu(2 * n + 1);
    
    for (auto a : edge) {
        int u = dsu.get(a[0]);
        int v = dsu.get(a[1]);
        dsu.oni(u, id_cnt);
        dsu.oni(v, id_cnt);
        tr[id_cnt].eb(u);
        tr[id_cnt].eb(v);
        pw[id_cnt] = a[2];
        id_cnt++;
    }
    return id_cnt - 1;
}

int n, q;
int dfn[mxN], rdfn[mxN], stmp;
// LCA binary jump
int up[mxN][21], dep[mxN];
const int mxL = 20;

void dfs(int u, int p = -1) {
	if (p != -1) up[u][0] = p;
    dfn[u] = ++stmp;
    rdfn[dfn[u]] = u;

	for (int i = 1; (1<<i) <= dep[u]; i++) 
		up[u][i] = up[up[u][i-1]][i-1];

	for (int v : tr[u]) {
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

inline int lca(int u, int v) {
	if (u == v) return u;
	if (dep[u] < dep[v]) swap(u, v);

	for (int i = mxL; i >= 0; i--) {
		if (up[u][i] and dep[up[u][i]] >= dep[v]) {
			u = up[u][i];
		}
	}

	if (u == v) return u;

	for (int i = mxL; i >= 0; i--) {
		if (up[u][i] and up[v][i] and up[u][i] != up[v][i]) {
			u = up[u][i];
			v = up[v][i];
		}
	}
	return up[u][0];
}

// segment tree
struct segment {
    int mn = inf, mx = 0, omn, omx, tag = -1;
} seg[mxN * 4];

#define ls x<<1
#define rs x<<1|1
#define mid ((l+r)>>1)

void upd(int x) {
    seg[x].mn = min(seg[ls].mn, seg[rs].mn);
    seg[x].mx = max(seg[ls].mx, seg[rs].mx);
    seg[x].omn = min(seg[ls].omn, seg[rs].omn);
    seg[x].omx = max(seg[ls].omx, seg[rs].omx);
}

void push_tag(int x, int v) {
    if (v) {
        seg[x].mn = inf;
        seg[x].mx = 0;
    } else {
        seg[x].mn = seg[x].omn;
        seg[x].mx = seg[x].omx;
    }
    seg[x].tag = v;
}

void down(int x) { 
    if (seg[x].tag != -1) {
        push_tag(ls, seg[x].tag);
        push_tag(rs, seg[x].tag);
        seg[x].tag = -1;
    }
}

void build(int l = 1, int r = n, int x = 1) {
	if(l == r) {
        seg[x].omx = seg[x].omn = dfn[l];
        seg[x].mx = 0;
        seg[x].mn = inf;
        seg[x].tag = -1;
		return;
	}
	build(l, mid, ls);
	build(mid+1, r, rs);
	upd(x);
}

void modify(int ql, int qr, int v, int l = 1, int r = n, int x = 1) {
    if (l != r) down(x);
	if(ql <= l && r <= qr) {
        push_tag(x, v);
        if (l != r) down(x);
		return;
	}
    if (ql <= mid) modify(ql, qr, v, l, mid, ls);
    if (qr > mid)  modify(ql, qr, v, mid+1, r, rs);
    upd(x);
}

inline void solve() {
    cin >> n >> q;
    vector<array<int, 3>> edge(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
    }

    int root = build_kruskal(edge);
    dfs(root);
    build();

    for (int i = 0; i < q; i++) {
        int op, l, r, x;
        cin >> op;
        if (op == 1 || op == 2) {
            cin >> l >> r;
            modify(l, r, (op - 1));
        } else {
            cin >> x;
            if (seg[1].mn == inf || seg[1].mx == 0) cout << -1 << '\n';
            else {
                int l = rdfn[seg[1].mn], r = rdfn[seg[1].mx];
                if (l == r && l == x) cout << -1 << '\n';
                else cout << pw[lca(x, lca(l, r))] << '\n';
            }
        }
    }
}

signed main() {
	IO;	
	solve();	
}
