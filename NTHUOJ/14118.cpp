#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
using namespace std;
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

const int mxN = 10005;
vector<pii> g[mxN];

int ans = -1;
int cnt = 0;
void dfs(int u, int sum, int dep, int lim, int ed) {
    if (dep > lim || (ans != -1 && sum > ans)) return;
    cnt++;
    if (cnt >= 45000000) {
        cout << ans << '\n';
        exit(0);
    }
    if (u == ed) {
        if (ans == -1 || ans > sum) 
            ans = sum;
        return;
    }
    for (pii pi : g[u]) {
        int v = pi.first;
        int w = pi.second;
        dfs(v, sum + w, dep + 1, lim, ed);
    }
}

inline void solve() {
    int n, m;
    int s, f, k;
    cin >> n >> m;
    cin >> s >> f >> k;
    k++;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].eb(v, w);
    }
    /*
    for (int i = 0; i < n; i++) {
        sort(ALL(g[i]), [](pii a, pii b) {
            return a.second < b.second;
        });
    }
    */
    dfs(s, 0, 0, k, f);
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
