#include<bits/stdc++.h>
using namespace std;
#define int long long
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

struct DSU {
	vector<int> dsu, sz, col, ll, rr;
	DSU(int n) {
		dsu.resize(n + 1);
		col.resize(n + 1);
		ll.resize(n + 1);
		rr.resize(n + 1);
		sz.resize(n + 1, 1);
		for (int i = 0; i <= n; i++) dsu[i] = col[i] = ll[i] = rr[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
	void oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return; 
		if(sz[a] > sz[b]) swap(a, b);
        ll[b] = min(ll[a], ll[b]);
        rr[b] = max(rr[a], rr[b]);
		dsu[a] = b;
		sz[b] += sz[a];
	}
};

inline void solve() {
    int n, q;
    cin >> n >> q;
    DSU dsu(n + 1);
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        cnt[i] = 1;
    }

    while (q--) {
        int op, x, c;
        cin >> op;
        if (op == 1) {
            cin >> x >> c;
            int px = dsu.get(x);
            int l = dsu.ll[px];
            int r = dsu.rr[px];
            if (c == dsu.col[px]) continue;
            cnt[dsu.col[px]] -= dsu.sz[px];
            cnt[c] += dsu.sz[px];
            dsu.col[px] = c;
            if (l > 1 && c == dsu.col[dsu.get(l - 1)]) {
                dsu.oni(x, l - 1);
            }
            if (r < n && c == dsu.col[dsu.get(r + 1)]) {
                dsu.oni(x, r + 1);
            }
            dsu.col[dsu.get(x)] = c;
        } else {
            cin >> x;
            cout << cnt[x] << '\n';
        }
    }
}

signed main() {
	IO;	
	solve();	
}
