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

struct Dijkstra {
    static const int mxN = 2e5 + 5;
    int n;
    vector<vector<pii>> G;

    Dijkstra(int _n) : n(_n), G(_n) {}

    void add_edge(int u, int v, int w) {
        G[u].eb(v, w);
        G[v].eb(u, w);
    }

    int dijkstra(int s, int t, int k) {
        #define P pair<int, pii>
        priority_queue<P, vector<P>, greater<P>> pq;
        vector<vector<int>> dis(k + 1, vector<int>(n + 1, -1));
        dis[0][s] = 0; 
        pq.push(0, mkp(0, s));

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            test(d, u.F, u.S);
            if (d > dis[u.F][u.S]) continue;
            for (auto [v, w] : G[u.S]) {
                test(v, w);
                if (dis[u.F][v] == -1 || dis[u.F][v] > d + w) {
                    dis[u.F][v] = d + w;
                    pq.push(dis[u.F][v], mkp(u.F, v));
                } 
                if (u.F + 1 <= k && (dis[u.F + 1][v] == -1 || dis[u.F + 1][v] > d)) {
                    dis[u.F + 1][v] = d;
                    pq.push(dis[u.F + 1][v], mkp(u.F + 1, v));
                } 
            }
        }

        int ans = INF;
        for (int i = 0; i <= k; i++) ans = min(ans, dis[i][t]);
        return ans;
    }
};

inline void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    Dijkstra dij(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dij.add_edge(u, v, w);
    }
    cout << dij.dijkstra(1, n, k) << '\n';
}

signed main() {
	IO;	
	solve();	
}
