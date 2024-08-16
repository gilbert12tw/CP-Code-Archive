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

#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 1e5 + 5;
// persistent segment tree
int n, q;
int tot;
int ls[mxN * 80], rs[mxN * 80], seg[mxN * 80];
int edit[mxN], tedit[mxN];
#define mid ((l+r)/2)

inline void up(int id) {
    seg[id] = seg[ls[id]] + seg[rs[id]];
}

inline void copy(int id, int p) {
    ls[id] = ls[p]; rs[id] = rs[p]; seg[id] = seg[p];
}

void modify(int &id, int pos, int v, int l = 1, int r = n) {
    int p = id;
    id = ++tot;
    copy(id, p); 
    seg[id] += v;
    if (l == r) return;
    if (pos <= mid) modify(ls[id], pos, v, l, mid);
    else modify(rs[id], pos, v, mid + 1, r);
    //up(id);
}

int query(int id, int k, int l = 1, int r = n) { // find >= k first pos
    if (l == r) return l; 
    if (k <= seg[ls[id]]) return query(ls[id], k, l, mid);
    return query(rs[id], k - seg[ls[id]], mid+1, r);
}

int adv_query(int a, int b, int c, int d, int k, int l = 1, int r = n) {
    int val = seg[ls[d]] - seg[ls[c]] + seg[ls[b]] - seg[ls[a]];
    if (l == r) return l;
    if (k <= val) return adv_query(ls[a], ls[b], ls[c], ls[d], k, l, mid);
    return adv_query(rs[a], rs[b], rs[c], rs[d], k - val, mid+1, r);
}

int qry(int id, int a, int b, int l = 1, int r = n) {
    if (b < a) return 0;
    if (a <= l && r <= b) return seg[id];
    ll res = 0;
    if (a <= mid) res += qry(ls[id], a, b, l, mid);
    if (b > mid) res += qry(rs[id], a, b, mid+1, r);
    return res; 
}

int aimer;
int dep[mxN], sz[mxN], dfn[mxN], L[mxN], R[mxN];
vector<int> tr[mxN];
int pa[20][mxN];

inline int jump(int x, int k) {
    for (int i = 18; i >= 0; i--) {
        if (get_bit(k, i)) x = pa[i][x];
    }
    assert(x != 0);
    return x;
}

void get_sz(int u) {
    sz[u] = 1;
    for (int i = 1; (1<<i) <= dep[u]; i++) 
        pa[i][u] = pa[i-1][pa[i-1][u]];

    for (int v : tr[u]) {
        dep[v] = dep[u] + 1;
        get_sz(v);
        sz[u] += sz[v];
    }
}

void dfs(int u) {
    dfn[++aimer] = u;
    L[u] = aimer;

    modify(edit[u], u, sz[u]);

    for (int v : tr[u]) {
        edit[v] = edit[u];
        modify(edit[v], u, -sz[v]);
        dfs(v);
    }
    R[u] = aimer;
}

inline void solve() {
    cin >> n >> q;
    int root = 0;
    for (int i = 1; i <= n; i++) {
        cin >> pa[0][i];
        if (pa[0][i] == 0) root = i;
        else tr[pa[0][i]].eb(i);
    }


    get_sz(root);
    dfs(root);

    for (int i = 1; i <= n; i++) {
        if (i > 1) tedit[i] = tedit[i - 1];
        modify(tedit[i], dfn[i], 1);
    }

    while (q--) {
        int k; cin >> k;
        int x = (k - 1) / n + 1;
        k = (k - 1) % n + 1;
        int lca = query(edit[x], k);
        k -= qry(edit[x], 1, lca - 1);
        assert(k > 0);

        int y, dl;
        if (lca == x) {
            y = adv_query(tedit[L[lca]-1], 0, 0, tedit[R[lca]], k);
        } else {
            dl = jump(x, dep[x] - dep[lca] - 1);
            y = adv_query(tedit[L[lca]-1], tedit[L[dl]-1], tedit[R[dl]], tedit[R[lca]], k);
        }

        cout << (x - 1) * n * n + (lca - 1) * n + (y - 1) << '\n';
    }
}

signed main() {
    IO;	
    solve();	
}
