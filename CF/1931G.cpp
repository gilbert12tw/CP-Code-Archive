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


consti int mxN = 2e6;
int n, J[mxN + 5], invJ[mxN + 5];
int fp(int a, int b, int p) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
 
void build(int n) {
    J[1] = J[0] = invJ[1] = invJ[0] = 1;
    for(int i = 2; i <= n; i++) J[i] = J[i - 1] * i % mod;
    invJ[n] = fp(J[n], mod - 2, mod);
    for(int i = n - 1; i >= 2; i--) invJ[i] = invJ[i + 1] * (i + 1) % mod;
}
 
int C(int n, int m) {
	if (n < m) return 0;
    if(n == m or m == 0) return 1;
    int res = J[n] * invJ[n - m] % mod * invJ[m] % mod;
    return res;
}

inline void solve() {
    vector<int> c(4);
    for (int &i : c) cin >> i;

    int delta = abs(c[1] - c[0]);

    if (delta > 1) {
        cout << 0 << '\n';
        return;
    }

    int ans = 0, n = max(c[0], c[1]);
    if (delta == 1) {
        for (int i = 1; i <= n; i += 2) {
            int res = 
            ans = (ans + );
        }
    } else {

    }
}

signed main() {
	IO;	
    int T; cin >> T;
    build(mxN);
	while (T--) solve();	
}
