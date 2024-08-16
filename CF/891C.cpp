#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
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
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 5e5 + 5, mxW = 5e5 + 5;

vector<pii> edge[mxW];
vector<pair<int, vector<int>>> qry[mxN]; // <query id, edge set>

struct DSU {
    int n;
	int pa[mxN], sz[mxN];
	vector<pii> stk;
	DSU(int _n) {
        n = _n;
		for (int i = 0; i <= n; i++) pa[i] = i, sz[i] = 1; 
	}
	int get(int u) { 
        while (pa[u] != u) u = pa[u];
        return u;
    }

	bool merge(int u, int v) {
		u = get(u), v = get(v);
		if (u == v) return 0;
		if (sz[u] > sz[v]) swap(u, v);
		sz[v] += sz[u];
		pa[u] = v;
		stk.eb(u, v);
		return 1;
	}

	int record() { return SZ(stk); }

	void roll_back(int keep_point) {
		while (SZ(stk) > keep_point) {
			pa[stk.back().F] = stk.back().F;
			sz[stk.back().S] -= sz[stk.back().F];
			stk.pop_back();
		}
	}
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    vector<pii> id_edge;
    int mx_weight = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        mx_weight = max(mx_weight, w);
        edge[w].eb(u, v);
        id_edge.eb(w, SZ(edge[w]) - 1);
    }
    
    int q; cin >> q;
    vector<int> ans(q, 1);
    for (int i = 0; i < q; i++) {
        int k; cin >> k;
        map<int, vector<int>> tmp;
        while (k--) {
            int id; cin >> id;
            id--;
            int w = id_edge[id].F;
            tmp[w].eb(id);
        }
        for (auto [val, v] : tmp) 
            qry[val].eb(i, v);
    }

    for (int i = 1; i <= mx_weight; i++) {
        for (auto [qry_id, v] : qry[i]) {
            int rcd = dsu.record();
            for (int e_id : v) {
                pii e = edge[id_edge[e_id].F][id_edge[e_id].S];
                if (!dsu.merge(e.F, e.S)) { 
                    ans[qry_id] = 0;
                    break;
                }
            }
            
            dsu.roll_back(rcd);
        }
         
        for (auto [u, v] : edge[i]) 
            dsu.merge(u, v);
    }

    for (int i = 0; i < q; i++) cout << (ans[i] ? "YES\n" : "NO\n");
}

signed main() {
	IO;	
	solve();	
}
