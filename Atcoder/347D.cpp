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
#define mod 1000000007
#define MOD 998244353
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

inline void solve() {
    int a, b, z;
    cin >> a >> b >> z;
    int c = __builtin_popcountll(z);
    int pa = a;
    int pb = b;

    int x = 0, y = 0; 
    int left = ((a + b) - c) / 2;

    for (int i = 0; i <= 60; i++) {
        if (left > 0 && get_bit(z, i) == 0) {
            left--;
            a--;
            b--;
            x |= (1ll<<i);
            y |= (1ll<<i);
        }
    }

    for (int i = 0; i <= 60; i++) {
        if (get_bit(z, i)) {
            if (a > 0) {
                a--;
                x |= (1ll<<i);
            } else if (b > 0) {
                b--;
                y |= (1ll<<i);
            }
        }
    }
    if ((x ^ y) != z || __builtin_popcountll(x) != pa || __builtin_popcountll(y) != pb) {
        cout << -1 << '\n';
        return;
    }
    cout << x << ' ' << y << '\n';
    return;
    cout << "test\n";
    cout << __builtin_popcountll(x) << '\n';
    cout << __builtin_popcountll(y) << '\n';
    int res = x ^ y;
    cout << res << '\n';
}

signed main() {
	IO;	
	solve();	
}
