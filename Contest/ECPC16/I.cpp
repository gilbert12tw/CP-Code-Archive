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

inline void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
}

const double eps = 10e-9;

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<double, int>> pt;
    for (int i = 0; i < n; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        if (y < 0) y = -y;
        if (y + r > m) continue;
        int rr = m - r;
        double dx = sqrt(1.0 * rr * rr - 1.0 * y * y);
        pt.eb(1.0 * x - dx - eps, r);
        pt.eb(1.0 * x + dx + eps, -r);
    }
    sort(ALL(pt));
    int sum = 0, mx = 0;
    for (auto [x, y] : pt) {
        sum += y;
        mx = max(mx, sum);
    }
    cout << mx << '\n';
}

signed main() {
	setIO("walk");	
    int T; cin >> T;
	while (T--) solve();	
}
