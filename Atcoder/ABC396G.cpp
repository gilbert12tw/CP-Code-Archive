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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<vector<int>> dp(m + 1, vector<int>((1<<m) + 1));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int t = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') t |= (1<<j);
        }
        dp[0][t]++;
    }
     
    for (int i = 0; i < m; i++) {
        for (int j = i; j >= 0; j--) {
            for (int b = 0; b < (1<<m); b++) {
                dp[j + 1][b ^ (1<<i)] += dp[j][b];
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < (1<<m); i++) {
        int res = 0;
        for (int j = 0; j < m; j++) {
            res += min(j, m - j) * dp[j][i];
        }
        ans = min(ans, res);
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
