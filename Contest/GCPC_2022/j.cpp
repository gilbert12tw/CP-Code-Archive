#include <bits/stdc++.h>
using namespace std;

int dp[100005][1 << 4][4];

template<class T>
void chmin(T& a, const T& b) {
    if (a > b) {
        a = b;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == 'c') {
            a[i] = 0;
        }
        if (c == 'h') {
            a[i] = 1;
        }
        if (c == 'd') {
            a[i] = 2;
        }
        if (c == 's') {
            a[i] = 3;
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    for (int c = 0; c < 4; c++) {
        dp[0][1 << c][c] = (a[0] != c);
    }
    // dp[0][1<<a[0]][a[0]] = 0;
    for (int i = 1; i < n; i++) {
        for (int mask = 0; mask < (1 << 4); mask++) {
            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 4; y++) {
                    if ((mask >> x & 1) == 0) continue;
                    if ((mask >> y & 1) && x != y) {
                        continue;
                    }
                    int new_mask = mask | (1 << y);
                    chmin(dp[i][new_mask][y], dp[i - 1][mask][x] + (a[i] != y));
                }
            }
        }
    }
    int ans = 1e9;
    for (int mask = 0; mask < (1 << 4); mask++) {
        ans = min(ans, *min_element(dp[n - 1][mask], dp[n - 1][mask] + 4));
    }
    cout << ans << "\n";

    // for (int i = 0; i < n; i++) {
    //     for (int mask = 0; mask < (1 << 4); mask++) {
    //         for (int c = 0; c < 4; c++) {
    //             if (dp[i][mask][c] > 100) continue;
    //             cout << i << " " << bitset<4>(mask).to_string() << " " << c << " = " << dp[i][mask][c] << "\n";
    //         }
    //     }
    // }

    return 0;
}
