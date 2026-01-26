#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define eb emplace_back
#define ALL(a) a.begin(), a.end()
#define SZ(a) ((int)a.size())

#ifdef debug
template <typename T>
ostream& operator << (ostream &o, vector<T> vec) {
    o << "{"; int f = 0; for (T i : vec) o << (f++ ? " " : "") << i; return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m"; (..., (cerr << a << " ")); cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#endif

void solve() {
    vector<pii> teams;
    for (int i = 0; i < 8; i++) {
        int a, b;
        cin >> a >> b;
        teams.eb(a, b);
    }
    vector<int> ord(8);
    iota(ALL(ord), 0);

    double ans = 0;

    auto match = [](const pii &a, const pii &b) -> double {
        return 1.0 * a.first / (1.0 * a.first + 1.0 * b.second);
    };
    auto check = [](int x, int y) -> int {
        int res = 0;
        for (int i = 0; i < 3; i++) {
            if ((x>>i) == (y>>i)) res++;
        }
        return res;
    };

    do {
        vector<vector<double>> dp(4, vector<double>(8));
        for (int i = 0; i < 8; i++) dp[0][i] = 1;

        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                for (int k = j + 1; k < 8; k++) {
                    if (check(ord[j], ord[k]) == 3 - i) {
                        if (ord[j] < ord[k]) {
                            double p = match(teams[j], teams[k]);
                            dp[i][j] += p * dp[i-1][k] * dp[i-1][j];
                            dp[i][k] += (1 - p) * dp[i-1][j] * dp[i-1][k];
                        } else {
                            double p = match(teams[k], teams[j]);
                            dp[i][k] += p * dp[i-1][j] * dp[i-1][k];
                            dp[i][j] += (1 - p) * dp[i-1][k] * dp[i-1][j];
                        }
                    }
                }
            }
        }

        ans = max(ans, dp[3][0]);
    } while (next_permutation(ALL(ord)));
    cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
