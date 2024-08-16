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
#define inf 2000000000
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
    int n;
    while (cin >> n && n) {
        vector<int> a(2 * n + 1);
        for (int i = 1; i <= 2 * n; i++) cin >> a[i];

        for (int i = 1; i <= 2 * n; i += 2) cout << i + 1 << ' ' << i << " \n"[i == 2 * n - 1];

        vector<int> ord(2 * n + 1);
        iota(ALL(ord), 0);
        sort(ord.begin() + 1, ord.end(), [&](int x, int y) {
            return a[x] < a[y];
        });

        vector<int> dp(2 * n + 1, inf), from(2 * n + 1, -1);
        dp[0] = 0;
        for (int i = 4; i <= 2 * n; i += 2) {
            /*
            if (i - 4 >= 0) {
                int cost = max(dp[i-4], max(abs(a[ord[i]] - a[ord[i-2]]), abs(a[ord[i-1]] - a[ord[i-3]])));
                if (cost < dp[i]) {
                    dp[i] = cost;
                    from[i] = i - 4;
                }
            }
            if (i - 6 >= 0) {
                int cost = max(dp[i-6], max({abs(a[ord[i]] - a[ord[i-3]]), abs(a[ord[i-1]] - a[ord[i-4]]), 
                                             abs(a[ord[i-2]] - a[ord[i-5]])}));
                if (cost < dp[i]) {
                    dp[i] = cost;
                    from[i] = i - 6;
                }
            }
            */
            for (int k = 2; k <= 10; k++) {
                if (i - 2 * k >= 0) {
                    int cost = 0;
                    for (int j = 0; j < k; j++) {
                        cost = max(cost, abs(a[ord[i-j]] - a[ord[i-j-k]]));
                    }
                    if (cost < dp[i]) {
                        dp[i] = cost;
                        from[i] = i - k * 2;
                    }
                }
            }
        }
        vector<int> ans(2 * n + 1);
        int ed = 2 * n;
        while (ed != 0) {
            /*
            if (from[ed] == ed - 4) {
                for (int i = 0; i < 2; i++) {
                    ans[ord[ed-i]] = ord[ed-i-2];
                    ans[ord[ed-i-2]] = ord[ed-i];
                }
                ed -= 4;
            } else {
                for (int i = 0; i < 3; i++) {
                    ans[ord[ed-i]] = ord[ed-i-3];
                    ans[ord[ed-i-3]] = ord[ed-i];
                }
                ed -= 6;
            }
            */
            int d = (ed - from[ed]) / 2;
            for (int i = 0; i < d; i++) {
                ans[ord[ed-i]] = ord[ed-i-d];
                ans[ord[ed-i-d]] = ord[ed-i];
            }
            ed -= d * 2;
        }
        //test(dp[2 * n]);
        for (int i = 1; i <= 2 * n; i++) cout << ans[i] << " \n"[i == 2 * n];
    }
}

signed main() {
	IO;	
	solve();	
}
