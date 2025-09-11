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
    int n; 
    cin >> n;
    vector<int> c(n), x(n);
    for (int &i : c) cin >> i, i--;
    for (int &i : x) cin >> i;


    for (int i = 0; i < n; i++) {
        c.eb(c[i]);
    }
    n = n * 2;

    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        dp[i][i] = x[c[i]] + 1;
        if (i > 0) dp[i][i-1] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                if (c[i] == c[j] && c[i] == c[k]) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j-1] + j - k);
                }
            }
            if (c[i] == c[j]) dp[i][j] = min(dp[i][j], dp[i+1][j-1] + x[c[i]] + len);
            if (c[j] == c[j-1]) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
            if (c[i] == c[i+1]) dp[i][j] = min(dp[i][j], dp[i+1][j] + 1);
        }
    }
    int ans = INF, hf = n / 2;
    for (int i = 0; i + hf - 1 < n; i++) {
        ans = min(ans, dp[i][i + hf - 1]);
        test(i, dp[i][i + hf - 1]);
    }
    test(dp[3][3]);
    test(dp[2][4]);
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
