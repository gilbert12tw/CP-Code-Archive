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
#define mod 1000000007
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

const int mxN = 101, mxB = 31;

int n, a[mxN];
int pre[mxB][mxN];
int dp[mxB][mxN][mxN];

void build() {
    for (int j = 0; j <= 30; j++) {
        for (int i = 1; i <= n; i++) 
            pre[j][i] = pre[j][i-1] + get_bit(a[i], j);
    }
}

int cost(int l, int r, int b, int one) {
    if (r < l) return 0;
    if (one) return (r - l + 1) - (pre[b][r] - pre[b][l-1]);
    return pre[b][r] - pre[b][l-1];
}

int DP(int l, int r, int b) {
    if (r < l) return 0;
    if (b < 0) return 0;
    if (~dp[b][l][r]) return dp[b][l][r];
    int res = INF;
    for (int k = l-1; k <= r; k++) {
        res = min(res, cost(l, k, b, 0) + cost(k+1, r, b, 1) + DP(l, k, b - 1) + DP(k + 1, r, b - 1));
    }
    return dp[b][l][r] = res;
}

inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> a[i];
    build();

    // DP
    // dp[b][i][j] -> interval [i, j] 
    memset(dp, -1, sizeof dp);
    cout << DP(1, n, 30);
}

signed main() {
	IO;	
	solve();	
}
