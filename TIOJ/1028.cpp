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
#define inf 10000000000000000
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
    vector<array<int, 3>> edge;
    for (int i = 0; i < m; i++) {
        int u, v, w; 
        cin >> u >> v >> w;
        edge.pb({u, v, w});
        edge.pb({v, u, w});
    }

    int k; cin >> k;

    int S = 0;
    vector<int> st(k);
    for (int &i : st) {
        cin >> i;
        S |= (1<<i);
    }

    vector<vector<int>> dp((1<<n), vector<int>(n, inf));
    vector<vector<string>> from((1<<n), vector<string>(n));
    dp[(1<<st[0])][st[0]] = 0;
    from[(1<<st[0])][st[0]] = 'a' + st[0];

    int mn = inf;
    string ans;
    for (int s = 0; s < (1<<n); s++) {
        // shorteset-path
        auto &dis = dp[s];
        auto &fm = from[s];
        for (int i = 0; i < n; i++) {
            for (auto [u, v, w] : edge) {
                if (get_bit(s, v)) {
                    if (dis[v] > dis[u] + w) {
                        fm[v] = fm[u] + char('a' + v);
                        dis[v] = dis[u] + w;
                    }
                    if (dis[v] == dis[u] + w) 
                        fm[v] = min(fm[v], fm[u] + char('a' + v));
                } else {
                    int ns = s | (1<<v);
                    if (dp[ns][v] > dis[u] + w) {
                        from[ns][v] = fm[u] + char('a' + v);
                        dp[ns][v] = dis[u] + w;
                    }
                    if (dp[ns][v] == dis[u] + w)
                        from[ns][v] = min(from[ns][v], fm[u] + char('a' + v));
                }
            }
        }
        if ((s & S) == S) {
            for (int u = 0; u < n; u++) {
                if (mn > dp[s][u]) {
                    mn = dp[s][u];
                    ans = from[s][u];
                } else if (mn != inf && mn == dp[s][u]) {
                    ans = min(ans, from[s][u]);
                }
            }
        }
    }
    cout << "Minimum travel distance: " << mn << '\n';
    cout << "Travel route:";
    for (char i : ans) cout << " " << (i - 'a');
}

signed main() {
    IO;	
    solve();	
}
