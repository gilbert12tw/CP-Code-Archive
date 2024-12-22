#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define x first
#define y second
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
    int n, x, k;
    cin >> n >> x >> k;
    map<int, vector<pii>> item;
    for (int i = 0; i < n; i++) {
        int p, v, c;
        cin >> p >> v >> c;
        item[c].eb(p, v);
    }

    vector<int> dp(x + 1, -INF);
    dp[0] = 0;
    for (auto [col, v] : item) {
        auto nxt_dp = dp; 
        for (auto [p, val] : v) {
            for (int i = x; i >= p; i--) {
                dp[i] = max(dp[i], dp[i - p] + val);             
                nxt_dp[i] = max(nxt_dp[i], nxt_dp[i - p] + val);
                nxt_dp[i] = max(nxt_dp[i], dp[i - p] + val + k);
            }
        }
        dp = move(nxt_dp);
    }
    cout << *max_element(ALL(dp)) << '\n'; 
}

signed main() {
	IO;	
	solve();	
}
