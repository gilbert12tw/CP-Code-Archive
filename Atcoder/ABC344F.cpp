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
#define inf 4000000000000000
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
    vector<int> p(n * n);
    vector<vector<int>> r(n, vector<int>(n)), d(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i * n + j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            cin >> r[i][j];
        }
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            cin >> d[i][j];
        }
    }

    vector<vector<int>> dis(n * n, vector<int>(n * n, inf));
    for (int i = 0; i < n * n; i++) {
        int x = i / n, y = i % n;
        for (int j = x; j < n; j++) {
            for (int k = y; k < n; k++) {
                if (j != x) ckmin(dis[i][j * n + k], dis[i][(j-1) * n + k] + d[j-1][k]);
                if (k != y) ckmin(dis[i][j * n + k], dis[i][j * n + k-1] + r[j][k-1]);
                if (j == x && k == y) dis[i][j * n + k] = 0;
                //test(j, k, dis[i][j * n + k], i, j * n + k);
            }
        }
    }

    auto best = [](pii a, pii b) {
        if (a.first > b.first) return b;
        if (a.first < b.first) return a;
        if (a.second > b.second) return a;
        return b;
    };

    p[n * n - 1] = inf;
    vector<pii> dp(n * n, mkp(inf, 0));
    dp[0] = mkp(0, 0); 
    for (int i = 0; i < n * n; i++) {
        int x = i / n, y = i % n;
        for (int j = 0; j < n * n; j++) {
            int nx = j / n, ny = i % n;
            if (nx > x || ny > y) continue;
            //if (p[j] > p[i]) continue;
            int dist = dis[j][i];
            int ac = max(0ll, (dist - dp[j].second) / p[j]);
            if (dp[j].second < dist && (dist - dp[j].second) % p[j] != 0) ac++;
            int lft = dp[j].second + ac * p[j] - dist;
            dp[i] = best(dp[i], mkp(ac + dp[j].first, lft));
        }
    }
    cout << dp[n * n - 1].first + (n - 1) * 2 << '\n';
}

signed main() {
	IO;	
	solve();	
}
