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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
    }

    for (int i = 0; i < q; i++) {
        int o, l, r;
        cin >> o;
        if (o == 1) {
            cin >> l;
            sum[l] += (a[l+1] - a[l]);
            swap(a[l], a[l+1]);
        } else {
            cin >> l >> r;
            cout << sum[r] - sum[l-1] << '\n';
        }
    }
}

signed main() {
	IO;	
	solve();	
}
