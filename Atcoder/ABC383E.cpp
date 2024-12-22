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

struct Edge {
    int u, v, w;
    bool operator < (Edge &b) {
        return w < b.w;
    };
};


struct DSU {
	vector<int> dsu, sz, cntA, cntB;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
        cntA.resize(n + 1, 0);
        cntB.resize(n + 1, 0);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}

	int oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return 0; 
		if(sz[a] > sz[b]) swap(a, b);
        int ca = cntA[a] + cntA[b];
        int cb = cntB[a] + cntB[b];
        int sub = min(ca, cb);

		dsu[a] = b;
		sz[b] += sz[a];
        cntA[b] = ca - sub;
        cntB[b] = cb - sub;
        return sub;
	}
};

inline void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<Edge> edge(m);
    for (int i = 0; i < m; i++) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    }

    DSU dsu(n + 1);
    for (int i = 0; i < k; i++) {
        int a; cin >> a;
        dsu.cntA[a]++;
    }
    for (int i = 0; i < k; i++) {
        int b; cin >> b;
        dsu.cntB[b]++;
    }
    
    sort(ALL(edge));
    int ans = 0;
    for (auto e : edge) {
        int u = e.u, v = e.v, w = e.w;
        if (dsu.get(u) == dsu.get(v)) continue;
        int cc = dsu.oni(u, v);
        test(u, v, w, cc);
        ans += w * cc;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
