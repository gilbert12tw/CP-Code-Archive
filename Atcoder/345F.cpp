#include<bits/stdc++.h>
#define loli
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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 2e5 + 5;
vector<int> g[mxN];

int vis[mxN], match[mxN];
int eu[mxN], ev[mxN];
vector<int> ans;

void dfs(int u, int p, int eid, int &k) {
    vis[u] = 1;
    for (int e : g[u]) {
        int v = eu[e] ^ ev[e] ^ u;
        if (vis[v]) continue;
        dfs(v, u, e, k);
    }
    if (p != -1 && !match[u] && k > 0) {
        if (match[u] == 0 && match[p] == 0) k -= 2;
        match[u] ^= 1;
        match[p] ^= 1;
        ans.eb(eid + 1);
    }
}

inline void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        g[eu[i]].eb(i);
        g[ev[i]].eb(i);
    }
    if (k % 2) {
        cout << "No\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i, -1, -1, k);
    }

    if (k == 0) {
        cout << "Yes\n";
        cout << SZ(ans) << '\n';
        for (int i : ans) cout << i << ' ';
    } else {
        cout << "No\n";
    }

}

signed main() {
	IO;	
	solve();	
}
