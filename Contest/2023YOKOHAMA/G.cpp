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
#define mod 998244353
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

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline int fp(int a, int b, int p) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
 
inline int inv(int x) {return fp(x, mod - 2, mod);}

unordered_map<int, int> dp[300005];
const int inv6 = inv(6);
int DP(int n, int k) {
    if (k > n) return 0;
    if (n <= 6) return inv(n);
    if (dp[n][k]) return dp[n][k];
    int res = 0;
    for (int i = 1; i <= 6; i++) {
        int subk = k / 6;
        int subn = n / 6;
        if (k % 6 == i % 6) continue;
        if (subk * 6 + i < k) subk++;
        if (subn * 6 + i <= n) subn++;
        res = (res + inv6 * DP(n - subn, k - subk) % mod) % mod;
    }
    return dp[n][k] = res;
}

inline void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << DP(n, i) << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
