#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
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
#define inf 1000000000000000000
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

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(n, inf));

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        ckmin(mat[a][b], c);
    }

    auto Dijkstra = [&](int st) {
        vector<int> vis(n, 0);
        int u = st;
        vector<int> dis = mat[st];

        for (int rd = 0; rd < n; rd++) {
            int mn = inf;
            for (int v = 0; v < n; v++) {
                if (vis[v] == 0 && dis[v] < mn) {
                    mn = dis[v];
                    u = v;
                }
            }
            if (mn == inf) break;
            vis[u] = 1;
            ckmin(dis[(u + 1) % n], dis[u] + 1);
            for (int v = 0; v < n; v++) {
                int tv = (dis[u] + v) % n;
                ckmin(dis[tv], dis[u] + mat[u][v]);
            }
        }

        dis[st] = 0;
        for (int i = 0; i < n; i++) {
            cout << dis[i] << " \n"[i == n - 1];
        }
        return;
    };

    for (int i = 0; i < n; i++) {
        Dijkstra(i);
    }
}

signed main() {
	IO;	
	solve();	
}
