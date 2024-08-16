#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define fi first
#define se second
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
    cerr << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 2e5 + 5;

int n, q;
int a[mxN];
vector<int> tr[mxN];

// lazytag segment tree
struct Node {
    int add = 0, mul = 1, zero = 0;
};

struct SegmentTree {
    Node seg[mxN * 4];
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    
    // a is the bson of b
    Node merge(Node a, Node b) {
        Node res;
        if (a.zero != 0) a.mul = 0;
        if (b.zero != 0) b.mul = 0;
        res.add = (a.add * b.mul % mod + b.add) % mod;
        res.mul = (a.mul * b.mul) % mod;
        res.zero = 0;
        return res;
    }

    inline void up(int x) {
        seg[x] = merge(seg[rs], seg[ls]);
    }

    void modify_zero(int pos, int ad, int l = 1, int r = n, int x = 1) {
        if (l == r) {
            seg[x].zero += ad;
            return;
        }
        if (pos <= mid) modify_zero(pos, ad, l, mid, ls);
        else  modify_zero(pos, ad, mid+1, r, rs);
        up(x);
    }

    void modify(int pos, int ad, int pd, int l = 1, int r = n, int x = 1) {
        if (l == r) {
            seg[x].add = ad;
            seg[x].mul = pd;
            return;
        }
        if (pos <= mid) modify(pos, ad, pd, l, mid, ls);
        else  modify(pos, ad, pd, mid+1, r, rs);
        up(x);
        test(l, r, seg[x].add, seg[x].mul);
    }

    void modify_val(int pos, int ad, int l = 1, int r = n, int x = 1) {
        if (l == r) {
            seg[x].add = ad;
            return;
        }
        if (pos <= mid) modify_val(pos, ad, l, mid, ls);
        else  modify_val(pos, ad, mid+1, r, rs);
        up(x);
    }

    void modify_mul(int pos, int pd, int l = 1, int r = n, int x = 1) {
        if (l == r) {
            seg[x].mul = seg[x].mul * pd % mod;
            return;
        }
        if (pos <= mid) modify_mul(pos, pd, l, mid, ls);
        else  modify_mul(pos, pd, mid+1, r, rs);
        up(x);
    }

    Node query(int a, int b, int l = 1, int r = n, int x = 1) {
        if(a <= l && r <= b) return seg[x];
        if(b > mid && a <= mid) 
            return merge(query(a, b, mid+1, r, rs), query(a, b, l, mid, ls));
        else if(a <= mid) 
            return query(a, b, l, mid, ls);
        return query(a, b, mid+1, r, rs);
    }
} segment;

// inversion
inline int fp(int a, int b, int p) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
inline int inv(int x) {
    if (x == 0) return 0;
    return fp(x, mod - 2, mod);
}

int tk, sz[mxN], fa[mxN], bson[mxN], tp[mxN], dep[mxN], dfn[mxN];
int tt[mxN], dp[mxN];

void dfs(int u, int p) { 
	sz[u] = 1; fa[u] = p; bson[u] = -1;
    dp[u] = 1;
	for (int v : tr[u]) {
		if(v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		sz[u] += sz[v];
		if(bson[u] == -1 || sz[v] > sz[bson[u]]) bson[u] = v;
        dp[u] = (dp[u] * dp[v]) % mod;
	}
    if (SZ(tr[u])) dp[u] = (dp[u] + a[u]) % mod;
    else dp[u] = a[u];
}

void link(int u, int p) {
	tp[u] = p; dfn[u] = ++tk;
    tt[p] = u; // tail of the chain
	if(bson[u] != -1) link(bson[u], p);
    int prod = 1, ze = 0;
	for(int v : tr[u]) {
		if(v == fa[u] || v == bson[u]) continue;
		link(v, v);
        if (dp[v] > 0) prod = prod * dp[v] % mod;
        else ze++;
	}
    segment.modify(dfn[u], a[u], prod);
    if (ze) segment.modify_zero(dfn[u], ze);
}

void jump(int u, int val) {
    int hsh = 0;
    a[u] = val;
    segment.modify_val(dfn[u], val);
    u = tt[tp[u]]; // go to tail
    while (tp[u] != 1) {
        Node res = segment.query(dfn[tp[u]], dfn[tt[tp[u]]]); 
        hsh = res.add;
        int iv = inv(dp[tp[u]]);
        dp[tp[u]] = hsh;
        u = fa[tp[u]];
        if (hsh != 0) segment.modify_mul(dfn[u], (hsh * (iv == 0 ? 1LL : iv)) % mod);
        if (hsh == 0 && iv != 0) segment.modify_zero(dfn[u], 1);
        if (hsh != 0 && iv == 0) segment.modify_zero(dfn[u], -1);
        test(hsh, iv);
    }
}

int qry() {
    Node ans = segment.query(dfn[1], dfn[tt[1]]);
    //test(ans.add, ans.mul, ans.zero);
    return ans.add;
}

inline void solve() {
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        tr[fa[i]].eb(i);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dfs(1, 0);
    link(1, 1);

    while (q--) {
        int v, x; cin >> v >> x;
        jump(v, x);
        cout << qry() << '\n';
    }
}

signed main() {
    IO;	
    solve();	
}
