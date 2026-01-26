#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    n += m;
    double S = (double) s / 2;
    S *= S;
    vector<double> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<double> pref(n + 1), pref2(n + 1);
    for(int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
        pref2[i + 1] = pref2[i] + a[i] * a[i];
    }
    auto calc_dist = [&](int l, int r) {
        int len = (r - l + 1);
        double r_sum = pref[r + 1] - pref[l];
        double mid_x = r_sum / len;
        double res = (pref2[r + 1] - pref2[l]) + mid_x * mid_x * len;
        res = res - 2 * r_sum * mid_x;
        return res;
    };
    vector<vector<double>> dist(n, vector<double>(n));
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            dist[i][j] = calc_dist(i, j);
        }
    }

    const double INF = 1E15;
    vector<vector<double>> dp(k + 1, vector<double>(n, INF));
    for(int j = 0; j < n; j++) {
        dp[1][j] = dist[0][j];
    }
    
    auto DP = [&](int k, int l, int r, int opt_l, int opt_r, auto self) -> void {
        int mid = (l + r) >> 1, opt = (opt_l + opt_r) >> 1;
        for (int i = opt_l; i <= opt_r && i < mid; i++) {
            if (dp[k-1][i] + dist[i+1][mid] < dp[k-1][opt] + dist[opt+1][mid]) 
                opt = i;
        }
        dp[k][mid] = dp[k-1][opt] + dist[opt+1][mid];
        if (l < mid) self(k, l, mid - 1, opt_l, opt, self);
        if (r > mid) self(k, mid + 1, r, opt, opt_r, self);
    };

    /*
    for(int i = 2; i <= k; i++) {
        for(int j = 0; j < n; j++) {
            for(int f = 0; f <= j; f++) {
                //double group = calc_dist(f, j);
                double group = dist[f][j];
                dp[i][j] = min(dp[i][j], (f - 1 >= 0 ? dp[i - 1][f - 1] : 0) + group);
            }
        }
    }
    */
    for (int i = 2; i <= k; i++) {
        DP(i, 0, n -1, 0, n - 1, DP);
    }
    cout << fixed << setprecision(10) << (S * n + dp[k][n - 1]) << "\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}
