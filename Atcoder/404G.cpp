#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
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

struct Edge {
    int u, v, w;
    Edge (int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    int s = n + 1;

    vector<Edge> edge;
    for (int i = 0; i < m; i++) {
        int l, r, s;
        cin >> l >> r >> s;
        edge.eb(Edge(l - 1, r, s));
        edge.eb(Edge(r, l - 1, -s));
    }
    for (int i = 1; i <= n; i++) {
        edge.eb(Edge(i, i - 1, -1));
        edge.eb(Edge(s, i, 0));
    }
    vector<int> dis(n + 2, 0), vis(n + 2, 0);
    dis[s] = 0; vis[s] = 1;
    bool ok = 1;

    for (int i = 0; i <= n + 1; i++) {
        for (auto [u, v, w] : edge) {
            if (!vis[u]) continue;
            if (!vis[v]) {
                vis[v] = 1;
                dis[v] = dis[u] + w;
            }
            dis[v] = min(dis[v], dis[u] + w);
        }
    }
    for (int i = 0; i <= n; i++) test(i, dis[i]);
    for (auto [u, v, w] : edge) {
        if (vis[u] && dis[v] > dis[u] + w) ok = 0;
    }
    int mn = INF;
    for (int i = 0; i <= n; i++) mn = min(mn, dis[i]); 
    if (ok && vis[n]) cout << dis[n] - mn << '\n';
    else cout << -1 << '\n';
}

signed main() {
	IO;	
	solve();	
}
