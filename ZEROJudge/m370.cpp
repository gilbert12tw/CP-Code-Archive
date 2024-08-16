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
    int n, x;
    cin >> x >> n;
    int cnt0 = 0, cnt1 = 0, ans = 0, mx = -10000, mn = 10000;
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        mx = max(mx, t);
        mn = min(mn, t);
        if (t < x) cnt0++;
        if (t > x) cnt1++;
        if (t == x) ans++;
    }
    if (cnt0 > cnt1) {
        cout << ans + cnt0 << ' ' << mn << '\n';
    } else {
        cout << ans + cnt1 << ' ' << mx << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
