#include<bits/stdc++.h>
#include<iomanip>
#define loli
using namespace std;
typedef long long ll;
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

double dp[10001][50];
double p2[100];

double pw(int k) {
    if (k == 0) return 0.0;
    return p2[k];
}

inline void solve() {
    int n;
    cin >> n;
    vector<pii> pt(n);
    p2[1] = 1;
    for (int i = 2; i <= 50; i++) p2[i] = p2[i-1] * 2;
    for (auto &i : pt) cin >> i;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 50; j++) {
            dp[i][j] = 1e15;
        }
    }
    dp[0][0] = 0;
    auto dis = [&](int i, int j) {
        return sqrt((pt[i].X - pt[j].X) * (pt[i].X - pt[j].X) + (pt[i].Y - pt[j].Y) * (pt[i].Y - pt[j].Y));
    };

    for (int i = 1; i < n; i++) {
        for (int k = 0; k < 50; k++) {
            dp[i][k] = min(dp[i][k], dp[i-1][k] + dis(i - 1, i));

            for (int j = 1; j <= k; j++) {
                if (i - j - 1 >= 0) 
                    dp[i][k] = min(dp[i][k], dp[i-j-1][k-j] + dis(i-j-1, i) - pw(k-j) + pw(k));
            }
        }
    }
    double ans = 1e15;
    for (int i = 0; i < 50; i++) ans = min(ans, dp[n-1][i]);
    cout << fixed << setprecision(10);
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
