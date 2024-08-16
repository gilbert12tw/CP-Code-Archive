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

const int mxN = 2e6 + 5;

int n, m;

vector<int> g[mxN], gd[mxN];

int low[mxN], dfn[mxN], id[mxN], cnt, dtm, sz = 0;
bitset<mxN> inst;
vector<int> st;

void tarjan(int u) {
    low[u] = dfn[u] = ++dtm;
    st.pb(u); inst[u] = 1;
    for(int v : gd[u]) {
        if(inst[v]) low[u] = min(low[u], dfn[v]);
        if(dfn[v]) continue;
        tarjan(v);
        low[u] = min(low[u], low[v]);
    }
    if(dfn[u] == low[u]) {
        int x;
        sz = SZ(st);
        do {
            x = st.back(); st.pop_back();
            id[x] = cnt;
            inst[x] = 0;
        } while(x != u);
         cnt++;
    }
}

bitset<mxN> vis, inn;
void dfs(int u, int p) {
    int f = 0;
    vis[u] = 1;
    inn[u] = 1;
    for (int v : g[u]) {
        if (v == p) {
            if (!f) f = 1;
            else gd[u].eb(v);
        } 
        else if (inn[v]) {
            gd[u].eb(v);
        }
        else if (!vis[v]) {
            dfs(v, u);
            gd[u].eb(v);
        }
    }
    inn[u] = 0;
}

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }

    for (int i = 1; i <= n; i++) if (!vis[i]) {
        dfs(i, 0);
    }

    tarjan(1);
    if (cnt == 1 && sz == n) {
        for (int i = 1; i <= n; i++) {
            for (int v : gd[i]) cout << i << ' ' << v << '\n';
        }
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
}

signed main() {
	IO;	
	solve();	
}
