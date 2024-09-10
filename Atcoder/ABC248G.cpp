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
#define mod 998244353
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
int a[mxN];
struct CentroidTree {
    vector<vector<pair<int, int>>> tree;

    vector<vector<int>> centroid_tree, dis;
    vector<int> del, pa, sz;

    CentroidTree(int n)
        : tree(n + 1, vector<pair<int, int>>()),
        centroid_tree(n + 1, vector<int>()), dis(n + 1, vector<int>()),
        del(n + 1), pa(n + 1), sz(n + 1, 1) {}

    void add_edge(int u, int v, int w = 1) {
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }

    void get_sz(int u, int p) {
        sz[u] = 1;
        for (auto [v, w] : tree[u]) {
            if (v == p || del[v])
                continue;
            get_sz(v, u);
            sz[u] += sz[v];
        }
    }

    int get_centroid(int u, int n, int p) {
        for (auto [v, w] : tree[u]) {
            if (v != p && !del[v] && sz[v] > n / 2)
                return get_centroid(v, n, u);
        }
        return u;
    }



    int build(int u, int &ans) {
        get_sz(u, -1);
        int centroid = get_centroid(u, sz[u], -1);
        u = centroid;
        del[centroid] = 1;

        map<int, int> mp, cnt;
        vector<pii> tmp;
        function<void(int, int, int, int)> dfs = [&](int u, int p, int g, int dep) {
            g = __gcd(a[u], g);
            tmp.eb(g, dep);
            for (auto [v, w] : tree[u]) {
                if (!del[v] && v != p) dfs(v, u, g, dep + 1);
            }
        };
        mp[a[u]] = 1;
        cnt[a[u]] = 1;
        for (auto [v, w] : tree[centroid]) {
            if (del[v]) continue;
            dfs(v, u, a[u], 1);
            for (auto [g1, v] : mp) {
                for (auto [g2, d] : tmp) {
                    ans = (ans + __gcd(g1, g2) * (cnt[g1] * d + v) % mod) % mod;
                }
            }
            for (auto [g, d] : tmp) {
                mp[g] += d + 1;
                cnt[g]++;
            }
            tmp.clear();
        }

        for (auto [v, w] : tree[centroid]) {
            if (del[v])
                continue;
            int tcd = build(v, ans);
            pa[tcd] = centroid;
            centroid_tree[centroid].emplace_back(tcd);
        }
        return centroid;
    }
};

inline void solve() {
    int n; cin >> n;
    CentroidTree CD(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        CD.add_edge(a, b);
    }
    int ans = 0;
    CD.build(2, ans);
    cout << ans << '\n';
}

signed main() {
    IO;	
    solve();	
}
