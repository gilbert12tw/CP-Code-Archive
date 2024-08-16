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
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline void solve() {
    int k;
    pii s, t;
    cin >> k;
    cin >> s.X >> s.Y;
    cin >> t.X >> t.Y;

    auto dis = [](pii a, pii b) {
        int res = llabs(a.X - b.X) + llabs(a.Y - b.Y);
        return res;
    };
    if ((s.X / k + s.Y / k) % 2 && (s.X / k == t.X / k && s.Y / k == t.Y / k)) {
        cout << 0 << '\n';
        return;
    }

    vector<pair<int, pii>> st, ed;
    if ((s.X / k + s.Y / k) % 2) {
        st.eb(0, mkp(s.X / k, s.Y / k));
    } else {
        int x = s.X / k, y = s.Y / k;
        test(x, y);
        st.eb(k - s.X % k, mkp(x + 1, y));  // right
        st.eb(s.X % k + 1, mkp(x - 1, y));  // left
        st.eb(k - s.Y % k, mkp(x, y + 1));  // up
        st.eb(s.Y % k + 1, mkp(x, y - 1));  // down
    }

    if ((t.X / k + t.Y / k) % 2) {
        ed.eb(0, mkp(t.X / k, t.Y / k));
    } else {
        int x = t.X / k, y = t.Y / k;
        ed.eb(k - t.X % k, mkp(x + 1, y));  // right
        ed.eb(t.X % k + 1, mkp(x - 1, y));  // left
        ed.eb(k - t.Y % k, mkp(x, y + 1));  // up
        ed.eb(t.Y % k + 1, mkp(x, y - 1));  // down
    }

    auto cal = [&](pii a, pii b) {
        int dx = llabs(a.X - b.X);
        int dy = llabs(a.Y - b.Y);
        if (dx > dy) swap(dx, dy);
        int res = 2 * dy;
        if (k == 2) res = min(res, dx + dx + ((dy - dx) / 2 * 3));
        return res;
    };

    int ans = dis(s, t);
    for (auto a : st) {
        for (auto b : ed) {
            test(a.X, b.X);
            ans = min(ans, a.X + b.X + cal(a.S, b.S));
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
