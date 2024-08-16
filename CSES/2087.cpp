#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<bitset>
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

const int mxN = 3000 + 5;

int n, k;
int c[mxN];
int dp[mxN][mxN]; // dp[k][i] = min cost when one school at i && total k schools
int pre[mxN][mxN];

int cost(int l, int r) {
    int mid = (l + r) >> 1;
    return pre[l][mid] + pre[r][mid+1];
}

void DP(int k, int l, int r, int optL, int optR) {
    if (l > r) return;
    int mid = (l + r) / 2;
    int opt = -1;
    dp[k][mid] = INF;
    
    for (int i = optL; i <= mid; i++) {
        if (dp[k-1][i] + cost(i, mid) < dp[k][mid]) {
            dp[k][mid] = dp[k-1][i] + cost(i, mid);
            opt = i;
        }
    }

    if (l == r) return;
        
    DP(k, l, mid - 1, optL, opt);
    DP(k, mid+1, r, opt, optR);
}

inline void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = l - 1; i >= 1; i--) {
            pre[l][i] = pre[l][i+1] + (l - i) * c[i];
        }
        for (int i = l+1; i <= n; i++) {
            pre[l][i] = pre[l][i-1] + (i - l) * c[i];
        }
        dp[1][l] = pre[l][1];
    }

    for (int j = 1; j <= k; j++) {
        if (j != 1) DP(j, 1, n, 1, n);
    }

    int ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[k][i] + pre[i][n]);
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
