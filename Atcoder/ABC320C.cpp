#include<bits/stdc++.h>
// #define loli
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

vector<int> dp[3][10];
inline void solve() {
    int m;
    string s[3];
    cin >> m;
    for (int i = 0; i < 3; i++) {
        cin >> s[i];
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < m; j++) {
                dp[i][s[i][j]-'0'].eb(j + k * m);
            }
        }
    }
    int ans = inf;
    for (int i = 0; i < 10; i++) {
        int res = inf;
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                for (int c = 0; c < 3; c++) {
                    if (SZ(dp[0][i]) <= a || 
                        SZ(dp[1][i]) <= b ||
                        SZ(dp[2][i]) <= c) 
                        continue;
                    if (dp[0][i][a] == dp[1][i][b] ||
                        dp[1][i][b] == dp[2][i][c] ||
                        dp[0][i][a] == dp[2][i][c])
                        continue;
                   res = min(res, max({dp[0][i][a], dp[1][i][b], dp[2][i][c]}));
                }
            }
        }
        test(res);
        ans = min(ans, res);
    }
    test(dp[0][3][0], dp[1][3][0], dp[2][3][0]);
    if (ans == inf) ans = -1;
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
