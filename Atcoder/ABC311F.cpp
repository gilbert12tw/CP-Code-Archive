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
#define mod 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 2005;
int dp[mxN][mxN];
int h[mxN];

char mat[mxN][mxN];

inline void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (mat[i] + 1);
    }

    h[0] = n;
    for (int j = 1; j <= m; j++) {
        int i = 0;
        while (i + 1 <= h[j-1] + 1 && i + 1 <= n && mat[i+1][j] != '#') i++;
        h[j] = i;
    }

    int ans = 0;
    dp[0][n + 1] = 1;
    for (int j = 1; j <= m; j++) {
        vector<int> suf(n + 2);
        suf[n+1] = dp[j-1][n+1];
        for (int i = n; i >= 1; i--)
            suf[i] = (suf[i+1] + dp[j-1][i]) % mod;
        for (int i = h[j] + 1; i >= 1; i--) {
            dp[j][i] = (dp[j-1][i-1] + suf[i]) % mod;
            if (j == m) ans = (ans + dp[j][i]) % mod;
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
