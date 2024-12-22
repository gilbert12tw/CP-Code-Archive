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

const double eps = 1e-10;

inline void solve(int cs) {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

#define pdd pair<double, double> 
    pdd rng(0, 1e9);

    auto clip = [&](pdd a, pdd b) -> pdd {
        return mkp(max(a.first, b.first), min(a.second, b.second));
    };

    double ans = 0;
    for (int i = 0; i < n; i++) {
        //pdd cur = mkp((1.0 * (i + 1)) / (1.0 * a[i]), (1.0 * (i + 1)) / (1.0 * b[i]));
        pdd cur = mkp((1.0 * a[i]) / (1.0 * (i + 1)), (1.0 * b[i]) / (1.0 * (i + 1)));
        
        rng = clip(cur, rng);
        if (rng.first > rng.second) {
            ans = -1.0;
            cout << fixed << setprecision(10) << "Case #" << cs << ": " << ans << '\n';
            return;
        }
    }

    if (rng.first <= rng.second) {
        if (fabs(rng.second) < eps) {
            ans = (1.0 * n) / 10.0;
        } else {
            ans = (1.0) / rng.second; 
        }
    }

    cout << fixed << setprecision(10) << "Case #" << cs << ": " << ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
    for (int i = 1; i <= T; i++) {
        solve(i);	
    }
}
