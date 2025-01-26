#include<bits/stdc++.h>
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
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
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

inline void solve() {
    int n;
    cin >> n;
    int invq = inv(10000);
    vector<int> a(n), p(n), rp(n);
    for (int &i : a) cin >> i;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        rp[i] = (10000 - p[i]) * invq % mod;
        p[i] = p[i] * invq % mod;
    }
    vector<int> dp(1024);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        vector<int> nxt(1024);
        for (int j = 0; j < 1024; j++) {
            nxt[j] = (nxt[j] + dp[j] * rp[i] % mod) % mod;
            nxt[j ^ a[i]] = (nxt[j ^ a[i]] + dp[j] * p[i] % mod) % mod; 
        }
        dp = nxt;
    }
    int ans = 0;
    for (int i = 0; i < 1024; i++) {
        ans = (ans + (i * i * dp[i] % mod)) % mod;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
