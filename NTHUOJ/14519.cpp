#include<bits/stdc++.h>
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

const int mxN = 805;
vector<int> dp[30][mxN];
vector<int> g[mxN];

inline void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dp[0][u].eb(v);
    }

    for (int i = 1; i <= 20; i++) {
        for (int u = 1; u <= n; u++) {
            vector<int> vis(n + 1);
            for (int v : dp[i-1][u]) {
                for (int v2 : dp[i-1][v]) {
                    if (vis[v2]) continue;
                    vis[v2] = 1;
                    dp[i][u].eb(v2);
                }
            }
        }
    }
    
    for (int u = 1; u <= n; u++) {
        vector<int> vis(n + 1);
        for (int i = 0; i <= 15; i++) {
            for (int v : dp[i][u]) {
                if (vis[v]) continue;
                vis[v] = 1;
                g[u].eb(v);
            }
        }
    }

    auto bfs = [&](int s, int t) -> int {
        queue<int> q; 
        q.push(s);
        vector<int> dis(n + 1, -1);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) return dis[t];
            for (int v : g[u]) {
                if (dis[v] != -1) continue;
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
        return -1;
    };

    cout << bfs(1, n) << '\n';
}

signed main() {
	IO;	
	solve();	
}
