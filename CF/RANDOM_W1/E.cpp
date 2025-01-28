#include<bits/stdc++.h>
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

// LCA
const int mxN = 200005;
const int lgN = 20;
int timer;
int in[mxN], out[mxN], dep[mxN], fa[lgN][mxN], sz[mxN];
vector<int> tree[mxN];
void dfs(int u = 1, int p = 1) {
    in[u] = ++timer;
    fa[0][u] = p;
    for (int i = 1; i < lgN; i++) 
        fa[i][u] = fa[i-1][fa[i-1][u]];
    sz[u] = 1;
    for (int v : tree[u]) {
        if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
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

int jump(int u, int k) {
    for (int i = lgN - 1; i >= 0; i--)  {
        if (get_bit(k, i)) u = fa[i][u];
    }
    return u;
}
 
inline int dis(int u, int v){
    test(u, v, lca(u, v));
    test(dep[u], dep[v], dep[lca(u, v)]);
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

inline void solve() {
    int n; cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].eb(b);
        tree[b].eb(a);
    }

    dfs(1);

    int m; cin >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        int d = dis(x, y);
        if (x == y) {
            cout << n << '\n';
            continue;
        }

        if (d % 2) {
            cout << 0 << '\n';
        } else {
            if (dep[x] == dep[y]) {
                int lx = jump(x, d / 2 - 1);
                int ly = jump(y, d / 2 - 1);
                cout << n - sz[lx] - sz[ly] << '\n';
            } else {
                if (dep[x] < dep[y]) swap(x, y);
                int lx = jump(x, d / 2 - 1);
                int llx = fa[0][lx];
                test(lx, llx, sz[llx], sz[lx]);
                cout << sz[llx] - sz[lx] << '\n';
            }
        }
    }
}

signed main() {
	IO;	
	solve();	
}
