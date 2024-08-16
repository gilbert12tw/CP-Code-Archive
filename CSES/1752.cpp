#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
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
 
const int mxN = 2e5 + 5, lgN = 20;
vector<int> tree[mxN];
int del[mxN], pa[mxN], sz[mxN], dep[mxN], val[mxN];
int in[mxN], out[mxN];
int fa[21][mxN];
 
inline void add_edge(int u, int v, int w = 1) {
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
}
 
int get_sz(int u, int p) {
    if (del[u]) return 0;
    sz[u] = 1;
    for (auto v : tree[u]) {
        if (v != p)
            sz[u] += get_sz(v, u);
    }
    return sz[u];
}
 
int get_centroid(int u, int n, int p) {
    for (auto v : tree[u]) {
        if (v != p && !del[v] && sz[v] > n / 2)
            return get_centroid(v, n, u);
    }
    return u;
}
 
// build the centroid tree recursively
int build(int u = 1) {
    get_sz(u, -1);
    int centroid = get_centroid(u, sz[u], -1);
    del[centroid] = 1;
 
    for (auto v : tree[centroid]) {
        if (!del[v]) 
            pa[build(v)] = centroid;
    }
    return centroid;
}
 
int timer;
void dfs(int u = 1, int p = 1) {
    in[u] = ++timer;
    fa[0][u] = p;
    for (int i = 1; i < lgN; i++) 
        fa[i][u] = fa[i-1][fa[i-1][u]];
    for (int v : tree[u]) {
        if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
    out[u] = ++timer;
}
bool ancestor(int u, int v){
    return in[u] <= in[v] && out[u] >= out[v];
}
 
int lca(int u, int v){
    if(ancestor(u, v))  return u;
    if(ancestor(v, u))  return v;
    for(int i = lgN-1; i >= 0; i--)
        if(!ancestor(fa[i][u], v))
            u = fa[i][u];
    return fa[0][u];
}
 
inline int dis(int u, int v){
    test(u, v, lca(u, v));
    test(dep[u], dep[v], dep[lca(u, v)]);
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

inline void upd(int x) {
    int u = x;
    val[u] = 0;
    while (pa[u]) {
        u = pa[u];
        val[u] = min(val[u], dis(u, x));
    }
}
 
inline int qry(int x) {
    int u = x, res = val[u];
    while (pa[u]) {
        u = pa[u];
        test(u, x, dis(u, x), val[u]);
        res = min(res, dis(u, x) + val[u]);
    }
    return res;
}

 
inline void solve() {
    int n, d;
    scanf("%d %d", &n, &d);
    if (n == d) {
        printf("1\n1\n");
        return;
    } else if (d == 1) {
        printf("%d\n", n);
        for (int i = 1; i <= n; i++) printf("%d ", i);
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    dfs(1, 1);
    build();
    vector<vector<int>> mp(n);
    for (int i = 1; i <= n; i++) {
        mp[dep[i]].eb(i);
        val[i] = inf;
    }
 
    vector<int> ans;
    for (int i = n - 1; i >= 0; i--) {
        //sort(ALL(mp[i]));
        random_shuffle(ALL(mp[i]));
        for (int v : mp[i]) {
            test(v, qry(v));
            if (qry(v) >= d) {
                upd(v); ans.eb(v);
            }
        }
    }
    printf("%d\n", SZ(ans));
    for (int i : ans) printf("%d ", i);
}
 
signed main() {
    IO;	
    solve();	
}
