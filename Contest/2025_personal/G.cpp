#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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
#define MOD 998244353
#define IO ios_base::sync_with_stdio(0); cin.tie(0);

inline void solve() {
    int n;
    cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    static int med[105][105];
    vector<vector<long double>> logMed(n+1, vector<long double>(n+1));
    for (int l = 1; l <= n; l++) {
        vector<int> v;
        v.reserve(n-l+1);
        for (int r = l; r <= n; r++) {
            v.pb(a[r]);
            auto u = v;
            sort(u.begin(), u.end());
            int m = r-l+1;
            int idx = (m-1)/2;
            med[l][r] = u[idx];
            logMed[l][r] = logl((long double)med[l][r]);
        }
    }

    const long double NEG_INF = -1e300L;
    vector<vector<long double>> dpLog(n+1, vector<long double>(n+1, NEG_INF));
    vector<vector<int>> dpMod(n+1, vector<int>(n+1, 0));
    dpLog[0][0] = 0.0L;
    dpMod[0][0] = 1;

    const long double eps = 1e-18L;
    for (int k = 1; k <= n; k++) {
        for (int i = k; i <= n; i++) {
            long double bestLog = NEG_INF;
            int bestMod = 0;
            for (int t = k-1; t <= i-1; t++) {
                if (dpLog[t][k-1] <= NEG_INF/2) continue;
                long double candLog = dpLog[t][k-1] + logMed[t+1][i];
                if (candLog > bestLog + eps) {
                    bestLog = candLog;
                    bestMod = (ll)dpMod[t][k-1] * med[t+1][i] % MOD;
                }
            }
            dpLog[i][k] = bestLog;
            dpMod[i][k] = bestMod;
        }
    }

    for (int k = 1; k <= n; k++) {
        cout << dpMod[n][k] << "\n";
    }
}

signed main() {
    IO;
    solve();
    return 0;
}
