#include<bits/stdc++.h>
//#define loli
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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool chmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool chmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

int n, m;

int DP(vector<vector<int>> &mat) {
    vector<vector<int>> pre(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] = pre[i-1][j] + pre[i][j-1] + mat[i][j] - pre[i-1][j-1];
        }
    }
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(n + 1, vector<int>(n + 1)));
    
    vector<int> mxr(n + 1);
    for (int i = m; i <= n; i++) {
        mxr[i] = mxr[i-1];
        for (int j = m; j <= n; j++) {
            int val = pre[i][j] - pre[i-m][j] - pre[i][j-m] + pre[i-m][j-m];
            dp[1][i][j] = max(dp[1][i-1][j], dp[1][i][j-1]);
            chmax(dp[1][i][j], dp[0][i-m][j] + val);
            chmax(dp[1][i][j], dp[0][i][j-m] + val);
            //chmax(dp[1][i][j], dp[0][i-m][j] + dp[0][i][j-m]);
            test(i, j, dp[0][i][j-m], dp[1][i][j], val);
            dp[0][i][j] = val;
            chmax(dp[0][i][j], dp[0][i-1][j]);
            chmax(dp[0][i][j], dp[0][i][j-1]);
            chmax(mxr[i], dp[1][i][j]);
            //test(i, j, dp[1][i][j], dp[0][i][j]);
        }
    }

    int ans = 0;
    int mx = 0;
    for (int i = n - m + 1; i >= 1; i--) {
        for (int j = 1; j + m - 1 <= n; j++) {
            int val = pre[i+m-1][j+m-1] - pre[i-1][j+m-1] - pre[i+m-1][j-1] + pre[i-1][j-1];
            //test(val);
            chmax(mx, val); 
        }
        test(i, mx, mxr[i-1]);
        chmax(ans, mx + mxr[i-1]);
    }
    return ans;
}

void reflex(vector<vector<int>> &mat) {
    for (int i = 1; i <= n; i++) 
        reverse(ALL(mat[i]));
}

void reflex_h(vector<vector<int>> &mat) {
    for (int i = 1; i <= n / 2; i++) 
        swap(mat[i], mat[n - i + 1]);
}

inline void solve() {
    cin >> n >> m;
    vector<vector<int>> mat(n + 1, vector<int>(n + 1)), mat_t;
    mat_t = mat;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mat[i][j];
            mat_t[j][i] = mat[i][j];
        }
    }

    int res = max(DP(mat), DP(mat_t));

    reflex(mat);
    reflex(mat_t);

    res = max(res, max(DP(mat), DP(mat_t)));

    reflex_h(mat);
    reflex_h(mat_t);

    res = max(res, max(DP(mat), DP(mat_t)));

    reflex(mat);
    reflex(mat_t);

    res = max(res, max(DP(mat), DP(mat_t)));
    cout << res;
}

signed main() {
	IO;	
	solve();	
}
