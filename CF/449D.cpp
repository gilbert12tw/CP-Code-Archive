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

const int mxB = 20;

inline void solve() {
    int n; cin >> n;
    vector<int> dp((1<<mxB));
    int msk = (1<<mxB) - 1;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        dp[(~a) & msk]++;
    }
    vector<int> bi(n + 1);
    bi[0] = 1;
    for (int i = 1; i <= n; i++) bi[i] = (bi[i-1] << 1) % mod;
    
    int ans = bi[n];

    // SoS
    for (int i = 0; i < mxB; i++) {
        for (int j = 0; j < (1<<mxB); j++) {
            if (get_bit(j, i)) dp[j] += dp[j ^ (1<<i)];
        }
    }

    for (int i = 0; i < (1<<mxB); i++) {
        dp[i] = bi[dp[i]];
    }
    test(dp[(1<<mxB) - 1]);

    // SoS reverse
    for (int i = 0; i < mxB; i++) {
        for (int j = 0; j < (1<<mxB); j++) {
            if (get_bit(j, i)) dp[j] = (dp[j] - dp[j ^ (1<<i)]) % mod;
            if (dp[j] < 0) dp[j] += mod;
        }
    }
    cout << dp[msk];
}

signed main() {
	IO;	
	solve();	
}
