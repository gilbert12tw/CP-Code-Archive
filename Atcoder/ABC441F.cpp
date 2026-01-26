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
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, -1));
    vector<vector<int>> from(n + 1, vector<int>(m + 1, -1));
    
    vector<pii> items;
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        int p, v;
        cin >> p >> v;
        items.eb(p, v);

        for (int j = 0; j <= m; j++) {
            ll chose = (j >= p ? dp[i-1][j-p] + v : -1);
            ll not_chose = dp[i-1][j];
            if (chose == -1 && not_chose == -1) {
                continue;
            } 
            if (chose == not_chose) {
                dp[i][j] = chose;
                from[i][j] = 2;
            } else if (chose > not_chose) {
                dp[i][j] = chose;
                from[i][j] = 1;
            } else {
                dp[i][j] = not_chose;
                from[i][j] = 0;
            }
        }
    }
    
    // Backtracking
    vector<vector<int>> tag(n + 1, vector<int>(m + 1, 0));
    ll mx = *max_element(ALL(dp[n]));
    for (int i = 1; i <= m; i++) {
        if (dp[n][i] == mx) tag[n][i] = 1;
    }
    bug(dp[n]);
    string ans;
    for (int i = n; i >= 1; i--) {
        ll p = items[i-1].first;
        ll v = items[i-1].second;
        vector<int> cnt(3);
        int tot = 0;
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == -1 || !tag[i][j]) continue;
            bug(from[i][j]);
            cnt[from[i][j]]++;
            tot++;
            if (j >= p && dp[i-1][j-p] + v == dp[i][j]) tag[i-1][j-p] = 1;
            if (dp[i-1][j] == dp[i][j]) tag[i-1][j] = 1;
        }
        bug(i, tot);
        assert(tot > 0);
        if (cnt[0] == tot) ans.push_back('C');
        else if (cnt[1] == tot) ans.push_back('A');
        else ans.push_back('B');
    }
    reverse(ALL(ans));
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
