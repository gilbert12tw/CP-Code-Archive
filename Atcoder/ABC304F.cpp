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

const int mxN = 2e5 + 5;
vector<int> divisor[mxN];

inline void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<int> dp(n + 1, 0), p2(n + 1);
    p2[0] = 1;
    for (int i = 1; i <= n; i++) p2[i] = p2[i-1] * 2 % mod;
    for (int i = 1; i <= n; i++) 
        for (int j = i+i; j <= n; j += i) divisor[j].eb(i);


    for (int i = 1; i < n; i++) {
        if (n % i) continue;
        vector<int> vis(i, 0);
        for (int j = 0; j < n; j++) {
            if (s[j] == '.')
                vis[j % i] = 1;
        }
        int cnt = 0;
        for (int j : vis) cnt += j;

        dp[i] = p2[i-cnt];

        for (int j : divisor[i]) { 
            if (i % j) continue;
            dp[i] -= dp[j];
            dp[i] %= mod;
            if (dp[i] < 0) dp[i] += mod;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + dp[i]) % mod;
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
