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

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> tag(11, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        int a, d, k;
        cin >> a >> d >> k;
        tag[d][a]++;
        tag[d][a + d * k]--;
    }

    for (int d = 1; d <= 10; d++) {
        for (int i = d; i <= n; i++) {
            tag[d][i] += tag[d][i-d];
        }
    }

    vector<int> vis(n + 1);

    auto check = [&](int x) {
        return 1 <= x && x <= n;
    };

    function<void(int)> dfs = [&](int u) {
        if (vis[u]) return;
        vis[u] = 1;
        for (int d = 1; d <= 10; d++) {
            if (check(u + d) && tag[d][u]) 
                dfs(u + d);
            if (check(u - d) && tag[d][u - d]) 
                dfs(u - d);
        }
    };

    int cc = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cc++;
            dfs(i);
        }
    }
    cout << cc << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
