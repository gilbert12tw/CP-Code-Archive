#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
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
const int mxN = 50000 + 5;
 
bitset<50001> reach[50001], vis;
vector<int> g[50001];
int n, m, q;

int low[mxN], dfn[mxN], id[mxN], cnt, dtm;
bitset<mxN> inst;
vector<int> st;
vector<int> tr[mxN], scc[mxN];

void tarjan(int u) {
    low[u] = dfn[u] = ++dtm;
    st.pb(u); inst[u] = 1;
    for(int v : g[u]) {
        if(inst[v]) low[u] = min(low[u], dfn[v]);
        if(dfn[v]) continue;
        tarjan(v);
        low[u] = min(low[u], low[v]);
    }
    if(dfn[u] == low[u]) {
        int x;
        do {
            x = st.back(); st.pop_back();
            scc[cnt].pb(x);
            id[x] = cnt;
            inst[x] = 0;
        } while(x != u);
        cnt++;
    }
}

void build_scc() {
    for (int i = 1; i <= n; i++) if (!dfn[i]) {
        tarjan(i);
    }

    vector<int> tmp(cnt + 1, 0);
    for (int i = 0; i < cnt; i++) {
        for (int u : scc[i]) {
            for (int v : g[u]) {
                if (id[v] != id[u] && tmp[id[v]] == 0) {
                    tr[i].eb(id[v]);
                }
            }
        }

        for (int u : scc[i]) {
            for (int v : g[u]) {
                tmp[id[v]] = 0;
            }
        }
    }

}
 
void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int v : tr[u]) {
        dfs(v);
        reach[u] |= reach[v];
    }
}
 
inline void solve() {
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].eb(v);
    }

    build_scc();
    for (int i = 0; i < cnt; i++) reach[i].set(i);
    for (int i = 0; i < cnt; i++) dfs(i);

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (reach[id[a]][id[b]]) cout << "YES\n";
        else cout << "NO\n";
    }

}
 
signed main() {
	IO;	
	solve();	
}
