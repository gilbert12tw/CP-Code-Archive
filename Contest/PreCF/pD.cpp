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
    vector<int> a(n + 1), b(m + 1), sum(n + 1);
    vector<vector<int>> nxt(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i-1] + a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] > b[j]) {
                nxt[i][j] = -1;
            } else {
                nxt[i][j] = ub(sum, sum[i - 1] + b[j]) - sum.begin() - 1;
            }
        }
    }

    vector<vector<pii>> dp(n + 1, vector<pii>(m + 2, mkp(INF, 0)));
    dp[0][0] = mkp(0, 1);

    auto madd = [](int &a, const int &b) {
        a += b;
        if (a >= mod) a -= mod;
        if (a < 0) a += mod;
    };

    auto upd = [&](pii &a, const pii &b) {
        if (a.F == b.F) madd(a.S, b.S);
        else if (b.F < a.F) a = b;
    };

    vector<map<int, int>> tag(m + 2), tcnt(m + 2);
    vector<vector<pii>> add(n + 1), del(n + 1);

    for (int i = 0; i <= n; i++) {
        for (auto [x, y] : add[i]) {
            madd(tag[y][dp[x][y].F + m - y], dp[x][y].S);
            tcnt[y][dp[x][y].F + m - y]++;
        }

        if (i != n) {
            for (int j = 1; j <= m; j++) {
                if (nxt[i+1][j] >= i + 1) {
                    add[i+1].eb(i, j);
                    del[nxt[i+1][j]].eb(i, j);
                }
            }
        }

        for (int j = 1; j <= m; j++) {
            upd(dp[i][j], dp[i][j-1]);
            if (!tag[j].empty()) upd(dp[i][j], *tag[j].begin());
        }

        for (auto [x, y] : del[i]) {
            madd(tag[y][dp[x][y].F + m - y], -dp[x][y].S);
            tcnt[y][dp[x][y].F + m - y]--;
            if (tcnt[y][dp[x][y].F + m - y] == 0) {
                tag[y].erase(dp[x][y].F + m - y);
            }
        }
    }

    pii ans = dp[n][m];
    if (ans.F == INF) { 
        cout << -1 << '\n';
        return;
    }
    cout << ans.F << ' ' << ans.S << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
