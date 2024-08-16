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

int code(char a, char b) {
    return (a - 'a') * 26 + (b - 'a');
}

inline void solve() {
    string s;
    cin >> s;
    vector<vector<int>> dp(26 * 26, vector<int>(26 * 26, inf));
    for (int i = 0; i < 26 * 26; i++) dp[i][i] = 0;

    for (int i = 1; i < SZ(s); i++) {
        dp[code(s[i-1], s[i])][code(s[i], s[i+1])] = 2;
        dp[code(s[i], s[i+1])][code(s[i-1], s[i])] = 2;
    }

    int n = 26 * 26;  
    for (int k = 0; k < n; k++) 
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);

    int q; 
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << 0 << '\n';
            continue;
        }
        l = code(s[l-1], s[l]);
        r = code(s[r-1], s[r]);
        if (l == r) {
            cout << 1 << '\n';
            continue;
        }

        

    }
}

signed main() {
	IO;	
	solve();	
}
