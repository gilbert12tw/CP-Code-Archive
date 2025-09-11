#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define fi first
#define se second
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
    int n, m;
    cin >> n >> m;
    vector<pii> p(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i].fi >> p[i].se;
    }
    sort(ALL(p), [](pii a, pii b) {
        return a.fi - a.se < b.fi - b.se;
    });

    int ptr = 0, stickers = 0;
    while (ptr < m) {
        if (n >= p[ptr].fi) {
            int a = p[ptr].fi;
            int b = p[ptr].se;
            int delta = a -b;
            int cnt = (n - a + delta) / delta;
            stickers += cnt;
            n = n - cnt * delta;
        }
        ptr++;
    }
    cout << stickers << '\n';
}

signed main() {
	IO;	
	solve();	
}
