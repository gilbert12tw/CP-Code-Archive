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

inline void solve() {
    int n; cin >> n;
    vector<vi> pa(25, vector<int>(n + 1));
    vi dep(n + 1);
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        if (l) pa[0][l] = i;
        if (r) pa[0][r] = i;
    }
    for (int i = n; i >= 1; i--) dep[i] = dep[pa[0][i]] + 1;

    auto lca = [&](int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);
        int k = dep[a] - dep[b];
        while (k--) {
            a = pa[0][a];
        }

        if (a == b) return a;

        while (a != b) {
            a = pa[0][a];
            b = pa[0][b];
        }
        return a;
        /*
        for (int i = 20; i >= 0; i--) {
            if (pa[i][a] != 0 && pa[i][b] != 0 && pa[i][a] != pa[i][b]) {
                a = pa[i][a];
                b = pa[i][b];
            }
        }
        */
        return pa[0][a];
    };

    int q; cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << max(lca(l, r), r) << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
