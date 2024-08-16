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

inline void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i] % x;
        a[i] /= x;
    }

    vector<vector<int>> dp(2, vector<int>(n, inf));
    dp[0][0] = a[0] + b[0];
    if (a[0]) dp[1][0] = a[0] - 1 + b[0] + x;

    auto cost = [](int a1, int b1, int a2, int b2) {
        if (a1 < 0 || b1 < 0 || a2 < 0 || b2 < 0) return (int)inf;
        return max(0ll, a2 - a1) + max(0ll, b2 - b1);
    };


    for (int i = 1; i < n; i++) {
        dp[0][i] = min(dp[0][i-1] + cost(a[i-1], b[i-1], a[i], b[i]), dp[1][i-1] + cost(a[i-1] - 1, b[i-1] + x, a[i], b[i]));
        dp[1][i] = min(dp[0][i-1] + cost(a[i-1], b[i-1], a[i]-1, b[i]+x), dp[1][i-1] + cost(a[i-1] - 1, b[i-1] + x, a[i] - 1, b[i] + x));
    }
    cout << min(dp[0][n-1], dp[1][n-1]) << '\n';
}

signed main() {
	IO;	
	solve();	
}
