#include<bits/stdc++.h>
#include<iomanip>
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

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> c(n);
    vector<vector<int>> s;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        int p;
        cin >> p;
        vector<int> tmp(p);
        for (int &j : tmp) cin >> j;
        s.eb(tmp);
    }

    vector<long double> dp(4 * m + 1, INF);
    dp[0] = 0.0;
    for (int i = 1; i <= 4 * m; i++) {
        for (int j = i - 1; j >= 0; j--) dp[j] = min(dp[j], dp[j+1]);

        for (int j = 0; j < n; j++){
            long double p = 1.0 * SZ(s[j]), res = 0;
            int cnt = 0;
            for (int k : s[j]) cnt += (k == 0);
            for (int k : s[j]) {
                if (!k) continue;
                res += (dp[max(i - k, 0ll)] / (p - cnt));
            }
            res += c[j] * p / (p - cnt);
            dp[i] = min(dp[i], res);
        }
    }
    long double ans = INF;
    for (int i = 4 * m; i >= m; i--) 
        ans = min(ans, dp[i]);
    cout << fixed << setprecision(5);
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
