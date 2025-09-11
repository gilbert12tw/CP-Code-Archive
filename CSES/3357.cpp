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

const int mxN = 2500 + 5;
int dis[2][mxN][mxN];

inline void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> G(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }

    memset(dis, -1, sizeof(dis));
    auto bfs = [&G](int st) -> void {
        queue<pii> q;
        q.push(st, 0);
        dis[0][st][st] = 0;
        
        while (!q.empty()) {
            auto [u, par] = q.front(); q.pop();
            int d = dis[par][st][u];
            par ^= 1;
            for (int v : G[u]) {
                if (dis[par][st][v] == -1) {
                    dis[par][st][v] = d + 1;
                    q.push(v, par);
                }
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        dis[0][i][i] = 0;
        bfs(i);
    }

    while (q--) {
        int u, v, x;
        cin >> u >> v >> x;
        if (dis[x & 1][u][v] == -1) {
            cout << "NO\n";
            continue;
        }
        if (dis[x & 1][u][v] > x) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
}

signed main() {
	IO;	
	solve();	
}
