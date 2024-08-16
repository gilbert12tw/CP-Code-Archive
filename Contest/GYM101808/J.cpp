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
    int l[2], r[2], p[2], d[2];
    for (int i = 0; i < 2; i++) 
        cin >> l[i] >> r[i] >> p[i] >> d[i];
    int k; cin >> k;
    int ans = 0;
    while (k--) {
        for (int i = 0; i < 2; i++) {
            if (d[i]) {
                if (p[i] == r[i]) {
                    p[i] = p[i] - 1;
                    d[i] ^= 1;
                } else {
                    p[i] = p[i] + 1;
                }
            } else {
                if (p[i] == l[i]) {
                    p[i] = p[i] + 1;
                    d[i] ^= 1;
                } else {
                    p[i] = p[i] - 1;
                }
            }
        }
        ans += (p[0] == p[1]);
        //test(p[0], p[1]);
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
