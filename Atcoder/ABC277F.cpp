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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j]; 
        }
    }

    vector<vector<vector<int>>> dp(k + 1, vector<vector<int>>(n, vector<int>(m, inf)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0) ckmin(dp[0][i][j], dp[0][i-1][j]);
            if (j > 0) ckmin(dp[0][i][j], dp[0][i][j-1]);
            for (int kk = 1; kk <= k; kk++) {
                if (i > 0) {
                    ckmin(dp[kk][i][j], dp[kk][i-1][j]);
                    ckmin(dp[kk][i][j], dp[kk-1][i-1][j] + a[i][j]);
                }
                if (j > 0) {
                    ckmin(dp[kk][i][j], dp[kk][i][j-1]);
                    ckmin(dp[kk][i][j], dp[kk-1][i][j-1] + a[i][j]);
                }

            }
        }
    }
    cout << dp[k][n-1][m-1] << '\n';
}

signed main() {
    IO;	
    solve();	
}
