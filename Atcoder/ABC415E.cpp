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

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    vector<int> p(n + m - 1);
    for (int &i : p) cin >> i;

    /*
    auto check = [&](int coin) -> bool {
        vector<vector<int>> dp(n, vector<int>(m, -1));
        dp[0][0] = coin + mat[0][0] - p[0];
        if (dp[0][0] < 0) return false;

        for (int d = 1; d < n + m; d++) {
            for (int i = 0; i < n; i++) {
                int j = (d - i);
                if (j < 0 || j >= m) continue;

                if (i > 0 && dp[i-1][j] >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j]);
                if (j > 0 && dp[i][j-1] >= 0) dp[i][j] = max(dp[i][j], dp[i][j-1]);

                dp[i][j] += mat[i][j];
                dp[i][j] -= p[d];
                //test(d, i, j, p[d]);
            }
        }
        //test(coin, dp[n-1][m-1]);
        return (dp[n-1][m-1] >= 0);
    };

    int l = 0, r = 2e15;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';
    */


    vector<vector<int>> dp(n, vector<int>(m, -1));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int day = i + j;
            int cost = p[day];
            int needs = 0;
            if (i == n - 1 && j == m - 1) {
                needs = 0;
            } else if (i == n - 1) {
                needs = dp[i][j + 1];
            } else if (j == m - 1) {
                needs = dp[i + 1][j];
            } else {
                needs = min(dp[i+1][j], dp[i][j+1]);
            }
            dp[i][j] = max(0ll, cost - mat[i][j] + needs);
        }
    }
    cout << dp[0][0] << '\n';
}

signed main() {
	IO;	
	solve();	
}
