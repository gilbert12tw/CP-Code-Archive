#include<bits/stdc++.h>
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
    vector<vector<int>> mat(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        mat[u][v] = mat[v][u] = 1;
    }

    vector<int> dp(1<<n, inf), from(1<<n, -1);
    // pre process
    for (int i = 0; i < (1<<n); i++) {
        int ok = 1;
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (mat[k][j] && get_bit(i, j) && get_bit(i, k)) {
                    ok = 0;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok) dp[i] = 1;
    }

    // O(3^n) DP
    for (int i = 1; i < (1<<n); i++) {
        for (int j = i; j > 0; j = (j - 1) & i) {
            if (dp[i] > dp[i ^ j] + dp[j]) {
                dp[i] = dp[i ^ j] + dp[j];
                from[i] = j;
            }
        }
    }
    cout << dp[(1<<n) - 1] << '\n';

    // dfs
    int col_cnt = 0;
    vector<int> col(n);
    auto dfs = [&](int st, auto&& dfs) -> void {
        if (st == 0) return;
        if (dp[st] == 1) {
            col_cnt++;
            for (int i = 0; i < n; i++) {
                if (get_bit(st, i)) col[i] = col_cnt;
            }
            return;
        }
        dfs(from[st], dfs);
        dfs(st ^ from[st], dfs);
    };
    dfs((1<<n)-1, dfs);
    for (int i : col) cout << i << ' ';
}

signed main() {
	IO;	
	solve();	
}
