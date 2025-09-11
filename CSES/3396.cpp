#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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


#define llu unsigned long long
inline llu add(llu a, llu b, llu c) { return (__int128{a} + b) % c; }
inline llu mul(llu a, llu b, llu c) { return __int128{a} * b % c; }
inline llu mpow(llu a, llu b, llu c) {
    llu res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, c);
        a = mul(a, a, c) ; b>>=1;
    }
    return res;
}
inline bool isprime(llu x) {
    if (x == 1) return false;

    static auto witn = [](llu a, llu n, int t) {
        if (!a) return false;
        while (t--) {
            llu a2 = mul(a, a, n);
            if (a2 == 1 && a != 1 && a != n - 1) return true;
            a = a2;
        }
        return a != 1;
    };
    if (x < 2) return false;
    if (!(x & 1)) return x == 2;
    int t = __builtin_ctzll(x - 1);
    llu odd = (x - 1) >> t;
    for (llu m:
            {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
    if (witn(mpow(m % x, odd, x), x, t))
        return false;
    return true;
}


inline void solve() {
    int n; cin >> n; n++;
    while (!isprime(n)) n++;
    cout << n << '\n';
}

signed main() {
    IO;	
    int T; cin >> T;
    while (T--) solve();	
}
