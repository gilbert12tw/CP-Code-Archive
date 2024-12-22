#pragma GCC optimize("Ofast, unroll-loops")
#include<bits/stdc++.h>
using namespace std;

int grid[20][20][20];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            for (int k = 0; k < n; ++ k) {
                cin >> grid[i][j][k];
            }
        }
    }

    vector<vector<int>> bits(n + 1);
    for (int i = 0; i < (1 << n); ++ i) {
        bits[__builtin_popcount(i)].push_back(i);
    }

    vector<vector<vector<int>>> f(n + 1, vector<vector<int>>((1 << n), vector<int>((1 << n), 2e9)));
    // vector<pair<int, int>> possi;
    f[0][0][0] = 0;
    for (int i = 1; i <= n; ++ i) {
        // int pre = ((i & 1) ^ 1);
        for (auto j : bits[i - 1]) {
            for (auto k : bits[i - 1]) {
                for (int x = 0; x < n; ++ x) {
                    if ((j >> x) & 1) continue;
                    for (int y = 0; y < n; ++ y) {
                        if ((k >> y) & 1) continue;
                        f[i][j | (1 << x)][k | (1 << y)] = min(f[i][j | (1 << x)][k | (1 << y)], f[i - 1][j][k] + grid[i - 1][x][y]);
                    }
                }
            }
        }
        // f[i].assign((1 << n), vector<int>((1 << n), 2e9));
    }
    int ans = 2e9;
    for (int i = 0; i < (1 << n); ++ i) {
        ans = min(ans, *min_element(f[n][i].begin(), f[n][i].end()));
    }

    cout << ans << "\n";
}