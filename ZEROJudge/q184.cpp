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
#define INF 2000000000000000000
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
    vector<int> a(n);
    for (int &i : a) cin >> i;


    multiset<int> up, down;
    int up_sum = 0, dn_sum = 0;

    auto keep = [&]() -> void {
        while (*down.rbegin() > *up.begin()) {
            int dt = *down.rbegin(); down.erase(prev(down.end()));
            int ut = *up.begin(); up.erase(up.begin());
            down.insert(ut); dn_sum += (ut - dt);
            up.insert(dt); up_sum -= (ut - dt);
        }
    };

    auto insert = [&](int x) -> void {
        if (SZ(down) <= SZ(up)) {
            down.insert(x);
            dn_sum += x;
        } else {
            up.insert(x);
            up_sum += x;
        }
        if (!down.empty() && !up.empty()) keep();
    };

    auto erase = [&](int x) -> void {
        if (down.find(x) != down.end()) {
            down.erase(down.find(x));
            dn_sum -= x;
        } else if (up.find(x) != up.end()) {
            up.erase(up.find(x));
            up_sum -= x;
        }

        while (SZ(up) < SZ(down) - 1) {
            int dt = *down.rbegin(); down.erase(prev(down.end()));
            dn_sum -= dt;
            up.insert(dt); up_sum += dt;
        }
    };

    auto cal = [&]() -> int {
        int median = *down.rbegin();
        return (up_sum - SZ(up) * median) + (SZ(down) * median - dn_sum);
    };

    sort(ALL(a));
    vector<int> pre(n, INF);
    for (int i = 0; i < n; i++) {
        insert(a[i]);
        if (i >= k - 1) {
            pre[i] = cal();
            pre[i] = min(pre[i], pre[i-1]);
            erase(a[i - k + 1]);
        }
    }

    // clear
    up.clear(); down.clear();
    dn_sum = up_sum = 0;

    int suf = INF, ans = INF;
    for (int i = n - 1; i >= 1; i--) {
        insert(a[i]);
        if (i + k - 1 < n) {
            suf = min(suf, cal());
            erase(a[i + k - 1]);
        }
        ans = min(ans, suf + pre[i-1]);
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
