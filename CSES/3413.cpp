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
    int n, k;
    cin >> n >> k;
    vector<string> mat(n);
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        dp[n-1][i] = 1;
        dp[i][n-1] = 1;
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            if (mat[i][j] == mat[i+1][j] && mat[i][j] == mat[i][j+1] && 
                mat[i][j] == mat[i+1][j+1]) {
                dp[i][j] = min({dp[i+1][j], dp[i][j+1], dp[i+1][j+1]}) + 1;
            }
            dp[i][j] = max(dp[i][j], 1ll);
        }
    }

    vector<int> ans(k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[mat[i][j] - 'A'] += dp[i][j];
            //test(mat[i][j], dp[i][j]);
        }
    }
    for (int i : ans) cout << i << '\n';
}

signed main() {
	IO;	
	solve();	
}
