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
    int n, m, p;
    cin >> m >> n >> p;
    vector<int> l(m), r(m);
    vector<int> tmp;
    for (int &i : l) cin >> i, tmp.eb(i);
    for (int &i : r) cin >> i, tmp.eb(i);
    tmp.eb(0); tmp.eb(n);
    sort(ALL(tmp));
    uni(tmp);

    n = SZ(tmp);
    vector<vector<int>> bus(n + 1);
    for (int i = 0; i < m; i++) {
        r[i] = lower_bound(ALL(tmp), r[i]) - tmp.begin();
        l[i] = lower_bound(ALL(tmp), l[i]) - tmp.begin();
        if (r[i] != 0 && r[i] > l[i]) bus[r[i]].eb(l[i]);
    }
    
    vector<int> dp(n + 1), sum(n + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int l : bus[i]) {
            int ad = (sum[i-1] - (l == 0 ? 0 : sum[l-1])) % p;
            if (ad < 0) ad += p;
            dp[i] = (dp[i] + ad) % p;
            dp[i] %= p;
            if (dp[i] < 0) dp[i] += p;
        }
        if (i) sum[i] = (dp[i] + sum[i-1]) % p;
        else sum[i] = dp[i];
        test(i, dp[i]);
    }
    cout << dp[n-1] << '\n';
}

signed main() {
	IO;	
	solve();	
}
