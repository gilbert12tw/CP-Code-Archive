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
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    int mx = *max_element(ALL(a));

    vector<int> cnt(mx+1), suf(mx+2);
    for (int i : a) cnt[i]++;

    for (int i = mx; i >= 0; i--) {
        suf[i] = suf[i+1] + cnt[i];
    }

    int ans = 0; 
    vector<int> dp(mx+5);
    for (int i = mx; i >= 1; i--) {
        int res = 0, sub = 0, ccnt = 0;
        for (int j = i; j <= mx; j += i) {
           sub += dp[j]; 
           res = res + ccnt * cnt[j] * suf[j + 1];
           if (cnt[j] > 1) res = res + ccnt * cnt[j] * (cnt[j] - 1) / 2;
           ccnt += cnt[j];
        }
        dp[i] = res - sub;
        ans += dp[i] * i;
    }
    for (int i = 1; i <= mx; i++) {
        if (cnt[i] > 1) {
            int cc = (cnt[i] * (cnt[i] - 1) / 2);
            ans = ans + cc * (suf[i + 1]) * i;
            ans = ans + (cnt[i] * (cnt[i] - 1) * (cnt[i] - 2) / 6) * i;
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
