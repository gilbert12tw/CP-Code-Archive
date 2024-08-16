#include<bits/stdc++.h>
#define loli
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
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

inline void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n+1);
    vector<vector<pii>> G(n + 1, vector<pii>());
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].eb(v, w);
    }

    vector<vector<int>> dp(n + 1, vector<int>((1<<k) + 1, inf));
    for (int i = 1; i <= n; i++) {
        dp[i][(1<<a[i])] = 0;
    }

    for (int cnt_k = 0; cnt_k < k; cnt_k++) {
        for (int i = 1; i <= n; i++) {
            for (int b = 1; b < (1<<k); b++) {
                if (dp[i][b] == inf) continue;
                for (auto [v, w] : G[i]) {
                    if (get_bit(b, a[v]) == 0) {
                        dp[v][b | (1<<a[v])] = min(dp[v][b | (1<<a[v])], dp[i][b] + w);
                    }
                }
            }
        }
    }

    int ans = inf;
    for (int i = 1; i <= n; i++) ans = min(ans, dp[i][(1<<k)-1]);
    if (ans == inf) {
        cout << "Ushio!";
        return;
    }
    cout << ans;
    
}

signed main() {
	IO;	
	solve();	
}
