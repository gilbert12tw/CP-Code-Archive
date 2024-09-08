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
#define inf 2000000000
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int all_sum = 0;
    for (int &i: a) cin >> i;
    for (int i = 0; i < n; i++) a.eb(a[i]), all_sum += a[i];

    auto check = [&](int mid) {
        vector<vector<int>> f(22, vector<int>(2 * n + 1, -1));
        int len = 0;
        for (int i = 0, j = 0; i < 2 * n; i++) {
            while (j < 2 * n && len < mid) 
                len += a[j++];
            if (len >= mid) f[0][i] = j;
            len -= a[i];
        }
        for (int j = 1; (1<<j) <= n; j++) {
            for (int i = 0; i < 2 * n; i++) {
                if (f[j-1][i] != -1)
                    f[j][i] = f[j-1][f[j-1][i]];
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int u = i;
            for (int j = 0; j <= 20; j++) {
                if (get_bit(k, j) && u != -1) 
                    u = f[j][u];
            }
            //test(i, u, k);
            if (u != -1 && u <= n + i) ans++;
        }
        return ans;
    };

    int l = 1, r = inf;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        test(mid);
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    cout << l << ' ' << n - check(l) << '\n';
}

signed main() {
	IO;	
	solve();	
}
