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
template <typename... T> void _print(T... args) {
    ((cerr << args << ' '), ...);
    cerr << '\n';
}
#ifdef debug
#define test(args...) _print("[" + string(#args) + "]:", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline void solve() {
    int n; 
    cin >> n;
    int mn[2] = {inf, inf};
    int mx[2] = {-inf, -inf};
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int pt[2];
        int x, y;
        cin >> x >> y;
        pt[0] = x + y;
        pt[1] = x - y; 

        for (int j = 0; j < 2; j++) {
            ans = max(ans, mx[j] - pt[j]);
            ans = max(ans, pt[j] - mn[j]);
        }
        cout << ans << '\n';

        for (int j = 0; j < 2; j++) {
            if (pt[j] > mx[j]) mx[j] = pt[j];
            if (pt[j] < mn[j]) mn[j] = pt[j];
        }
    }
}

signed main() {
	IO;	
	solve();	
}
