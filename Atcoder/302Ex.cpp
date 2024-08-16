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

struct DSU {
    int n, edges, cnt;
    vector<int> tag, pa, sz;
    vector<array<int, 3>> stk;
    DSU(int _n): n(_n), edges(0), cnt(0), tag(_n+1), pa(_n+1), sz(_n+1, 1) {
        for (int i=1;i<=n;i++) pa[i] = i;
    }
    int get(int u) { 
        while (u != pa[u]) u = pa[u];
        return u;
    }
    void merge(int u, int v) {
        u = get(u), v = get(v);
        if (u == v) {
            if (tag[u]++ == 0) cnt++;
            stk.eb(array<int, 3>{-1, u, 1});
            test(u, v, tag[u]);
            return;
        }
        if (sz[u] > sz[v]) swap(u, v);
        stk.eb(array<int, 3>{u, v, tag[u]});
        if (tag[u] > 0 && tag[v] > 0) cnt--;
        edges++;
        tag[v] += tag[u];
        sz[v] += sz[u];
        pa[u] = v;
        return;
    }
    int record() { return (int)(stk.size()); }
    void roll_back(int keep_point) {
        while (SZ(stk) > keep_point) {
            int u = stk.back()[0], v = stk.back()[1], t = stk.back()[2]; stk.pop_back();
            tag[v] -= t;
            if (tag[v] == 0 && u == -1) cnt--;
            if (u == -1) continue;
            edges--;
            if (tag[u] > 0 && tag[v] > 0) cnt++;
            pa[u] = u;
            sz[v] -= sz[u];
        }
    }
};

const int mxN = 2e5 + 5;
int a[mxN], b[mxN], vis[mxN], ans[mxN];
vector<int> tr[mxN];
DSU dsu(200000);

void dfs(int u, int p) {
    test("F", u, dsu.edges, dsu.cnt);
    int rc = dsu.record(); 
    dsu.merge(a[u], b[u]);
    ans[u] = dsu.edges + dsu.cnt;
    for (int v : tr[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    dsu.roll_back(rc);
    test("S", u, dsu.edges, dsu.cnt);
}

inline void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v; 
        cin >> u >> v;
        tr[u].eb(v);
        tr[v].eb(u);
    }

    dfs(1, 0);

    for (int i = 2; i <= n; i++)
        cout << ans[i] << ' ';
}

signed main() {
    IO;	
    solve();	
}
