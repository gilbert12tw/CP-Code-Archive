#include<bits/stdc++.h>
//#define loli
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
int n;
int s[mxN], k[mxN], r[mxN];
vector<int> g[mxN];

inline void solve() {
    cin >> n;
    vector<int> ind(n + 1, 0), del(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> k[i] >> r[i];
        ind[i] = r[i];
        for (int j = 0; j < r[i]; j++) {
            int x; cin >> x;
            g[x].eb(i);
        }
    }

    vector<int> dp(n + 1), ksum(n + 1, 0);
    queue<int> q;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 1; i <= n; i++) { 
        dp[i] = k[i];
        ksum[i] = s[i];
        pq.push(k[i], i);
        if (ind[i] == 0) {
            del[i] = 1;
            q.push(i);
        }
    }

    while (!q.empty() || !pq.empty()) {
        if (q.empty()) {
            while (!pq.empty()) {
                auto [v, id] = pq.top(); pq.pop();
                if (del[id] == 0) {
                    del[id] = 1;
                    q.push(id);
                    break;
                }
            }
        } else {
            int u = q.front(); q.pop();
            test(u);
            //dp[u] = min(dp[u], ksum[u]);
            for (int v : g[u]) {
                ind[v]--;
                ksum[v] += dp[u];
                if (!del[v] && ind[v] == 0) {
                    test(u, v);
                    q.push(v);
                    dp[v] = min(dp[v], ksum[v]);
                    del[v] = 1;
                }
            }
        }
    }
    cout << dp[1] << '\n';

}

signed main() {
	IO;	
	solve();	
}
