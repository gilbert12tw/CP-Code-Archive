#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
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

const int MN = 5e5 + 5;
// BCC
int n, m, cnt;
vector<int> g[MN], tree[MN * 2];

int bcc[MN];
int dfn[MN], low[MN], dfc, num;
int stk[MN], tp;

void Tarjan(int u) {
    low[u] = dfn[u] = ++dfc;
    stk[++tp] = u;
    ++num;
    for (int v : g[u]) {
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                cnt++;
                for (int x = 0; x != v; --tp) {
                    x = stk[tp];
                    tree[cnt].push_back(x);
                    tree[x].push_back(cnt);
                }
                tree[cnt].push_back(u);
                tree[u].push_back(cnt);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int pa[MN * 2];
void dfs(int u, int p = -1) {
    pa[u] = p;
    for (int v : tree[u]) {
        if (v != p)
            dfs(v, u);
    }
}

int check(int a, int b, int c) {
    vector<int> cnt(3 * n, 0);
    for (int v : tree[a]) if (v > n) cnt[v]++;
    for (int v : tree[b]) if (v > n) cnt[v]++;
    for (int v : tree[c]) if (v > n) cnt[v]++;
    return *max_element(ALL(cnt)) == 3;
}

int check(int a, int b) {
    vector<int> cnt(3 * n, 0);
    for (int v : tree[a]) if (v > n) cnt[v]++;
    for (int v : tree[b]) if (v > n) cnt[v]++;
    return *max_element(ALL(cnt)) == 2;
}

inline void solve() {
    cin >> n >> m;
    int a, b, c;
    cin >> a >> b >> c;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }

    cnt = n+1;
    Tarjan(a);
    dfs(a);
    
    if (check(a, b, c)) {
        cout << "Yes\n";
        return;
    } else if (check(a, b) && pa[c] != 0) {
        cout << "Yes\n";
        return;
    } 

    vector<int> vb(n * 3, 0);
    for (int v : tree[b]) if (v > n) vb[v] = 1;

    int u = c, ok = 0;
    while (u && u != -1) {
        //test(u);
        if (vb[u]) {
            ok = 1;
            break;
        }
        u = pa[u];
    }
    if (ok) cout << "Yes\n";
    else cout << "No\n";
}

signed main() {
    IO;	
    solve();	
}
