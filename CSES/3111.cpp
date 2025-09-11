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


struct DSU {
	vector<int> dsu, sz;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
	void oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return; 
		if(sz[a] > sz[b]) swap(a, b);
		dsu[a] = b;
		sz[b] += sz[a];
	}
};

inline void solve() {
    int n;
    cin >> n;
    vector<pair<int, pii>> edges;

    for (int i = 0; i < n - 1; i ++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.eb(w, mkp(u, v));
    }
    sort(ALL(edges));
    reverse(ALL(edges));

    DSU dsu(n);
    int ans = 0;
    for (auto [w, p] : edges) {
        int x = dsu.get(p.f);
        int y = dsu.get(p.s);
        ans += w * dsu.sz[x] * dsu.sz[y];
        dsu.oni(x, y);
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
