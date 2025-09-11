#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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
    int n;
    vector<vector<pii>> g;
    Dijkstra(int _n) : n(_n + 1), g(_n + 1) {}

    void add_edge(int u, int v, int w) {
        g[u].eb(v, w);
        // g[v].eb(u, w);
    }

    vector<int> dijkstra(int s) {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vector<int> dis(n, -1); dis[s] = 0; pq.push(0, s);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dis[u]) continue;
            for (auto [v, w] : g[u]) {
                if (dis[v] == -1 || dis[v] > d + w) {
                    dis[v] = d + w;
                    pq.push(dis[v], v);
                } 
            }
        }
        return dis;
    }
};

inline void solve() {
    int n, m;   
    cin >> n >> m;
    vector<int> c(m);
    for (int &i : c) cin >> i;
    Dijkstra dij(n + m);
    int cnt = n;
    for (int i = 0; i < m; i++) {
        int k; cin >> k;
        cnt++;
        while (k--) {
            int x; cin >> x;
            x--;
            dij.add_edge(x, cnt, c[i]);
            dij.add_edge(cnt, x, 0);
        }
    }
    vector<int> ans = dij.dijkstra(0);
    ans.resize(n);
    for (int i : ans) cout << i << ' ';
}

signed main() {
	IO;	
	solve();	
}
