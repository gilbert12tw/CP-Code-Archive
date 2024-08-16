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

// (a1, b1), (a2, b2)
// a1 * (a2 + b2) + b1 = a1 * a2 * k + a1 * b2 + b1
// a2 * (a1 + b1) + b2 = a2 * a1 * k + a2 * b1 + b2


inline void solve() {
    int n, k;
    cin >> n >> k;
    vector<pii> p(n);
    for (auto &pr : p) cin >> pr.F >> pr.S;
    sort(ALL(p), [](pii a, pii b) {
        return a.F * b.S + a.S < b.F * a.S + b.S;
    });
    vector<vector<int>> dp(k + 1, vector<int>(n));
    dp[0][0] = 1;
    dp[1][0] = p[0].F + p[0].S;
    for (int i = 1; i < n; i++) {
        dp[0][i] = 1;
        for (int j = 1; j <= k; j++) {
            dp[j][i] = max(dp[j][i-1], dp[j-1][i-1] * p[i].F + p[i].S);
        }
    }
    cout << dp[k][n-1] << '\n';
}

signed main() {
	IO;	
	solve();	
}
