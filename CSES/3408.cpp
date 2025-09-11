#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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
  int n;
  vector<int> pa, sz;
  vector<pii> stk;
  DSU(int _n): n(_n), pa(_n+1), sz(_n+1, 1) {
    for (int i=1;i<=n;i++) pa[i] = i;
  }
  int get(int u) { 
    while (u != pa[u]) u = pa[u];
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
  int record() { return (int)(stk.size()); }
  void roll_back(int keep_point) {
    while (SZ(stk) > keep_point) {
      pa[stk.back().F] = stk.back().F;
      sz[stk.back().S] -= sz[stk.back().F];
      stk.pop_back();
    }
  }
};

struct Edge {
    int u, v, w;
};

inline void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> edges, sorted_edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.eb(u, v, w);
    }
    sorted_edges = edges;
    sort(ALL(sorted_edges), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    map<int, vector<pair<int, vector<int>>>> qry;
    for (int i = 0; i < q; i++) {
        int k; cin >> k;
        vector<pii> tmp;
        while (k--) {
            int eid; cin >> eid;
            eid--;
            tmp.eb(edges[eid].w, eid);
        }
        sort(ALL(tmp));

        vector<int> gp;
        for (int j = 0; j < SZ(tmp); j++) {
            gp.eb(tmp[j].s);
            if (j == SZ(tmp) - 1 || tmp[j+1].f != tmp[j].f) {
                qry[tmp[j].f].eb(mkp(i, gp));
                gp.clear();
            }
        }
    }

    DSU dsu(n);
    vector<int> ans(q, 1);
    int ptr = 0;
    for (auto [w, vvv] : qry) {
        while (ptr < m && sorted_edges[ptr].w < w) {
            dsu.merge(sorted_edges[ptr].u, sorted_edges[ptr].v);
            ptr++;
        }
        int rd = dsu.record();
        test(w);
        for (auto [qi, vv] : vvv) {
            for (auto eid : vv) {
                int u = edges[eid].u, v = edges[eid].v;
                test(qi, u, v, ans[qi]);
                if (!dsu.merge(u, v)) {
                    ans[qi] = 0;
                    break;
                }
            }
            dsu.roll_back(rd);
        }
    }
    for (int i : ans) cout << (i ? "YES" : "NO") << '\n';
}

signed main() {
    IO;	
    solve();	
}
