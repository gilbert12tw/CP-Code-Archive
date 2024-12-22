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
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    vector<int> lst(50, -1);
    vector<pii> seg[50];
    for (int i = 0; i < n; i++) {
        if (lst[a[i]] != -1) {
            seg[a[i]].eb(lst[a[i]], i);
        }
        lst[a[i]] = i;
    }
    
    vector<int> dp(1<<20, inf);
    dp[0] = -1;
    int ans = 0;
    for (int i = 1; i < (1<<20); i++) {
        for (int j = 0; j < 20; j++) {
            if (get_bit(i, j) == 0) continue;
            if (seg[j + 1].empty()) continue;
            int pt = dp[i ^ (1<<j)];
            if (pt == inf) continue;
            auto it = lower_bound(ALL(seg[j + 1]), mkp(pt, inf * 1LL));
            if (it == seg[j + 1].end()) continue;
            ckmin(dp[i], it -> second);
        }
        if (dp[i] < n) {
            ans = max(ans, int(__builtin_popcountll(i)));
        }
    }
    cout << 2 * ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
