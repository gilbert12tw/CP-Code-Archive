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

inline void solve() {
    int n, k;
    cin >> n >> k;

    int l = max(1ll, k - n);
    int r = min(n, k);

    int ans = 0;

    map<pair<char, int>, int> mp;
    auto ask = [&mp, &n, &k](char c, int x) -> int {
        if (x < k - n || x < 1 || 
            x > n || x > k) return -INF;
        if (mp.find(mkp(c, x)) != mp.end())
            return mp[mkp(c, x)];
        cout << c << ' ' << x << endl;
        int res; cin >> res;
        mp[mkp(c, x)] = res;
        return res;
    };

    auto f = [&](int x) -> int {
        assert(x <= k && x >= 1);
        int res = max(ask('F', x), ask('S', k - x + 1));
        return res;
    };

    auto check = [&](int x) -> bool {
        int a = f(x - 1);
        int b = f(x);
        return a > b;
    };

    // k = 1
    if (k == 1) {
        int ans = max(ask('F', 1), ask('S', 1));
        cout << "! " << ans << endl;
        return;
    }
    if (k == 2 * n) {
        int ans = min(ask('F', n), ask('S', n));
        cout << "! " << ans << endl;
        return;
    }

    bool fi = true;
    while (l < r) {
        test(l, r);
        int mid = (l + r + 1) >> 1;
        if (fi) {
            mid = min(l + 20, r);
            fi = false;
        }
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    ans = f(l);
    cout << "! " << ans << endl;
}

signed main() {
	IO;	
	solve();	
}
