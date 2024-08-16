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

const int mxN = 2000;
set<pii> G[mxN];
vector<int> ans;
int vis[mxN], in[mxN];

void dfs(int u) {
    for (auto [e, v] : G[u]) {
        if (vis[e]) continue;
        vis[e] = 1;
        dfs(v);
        ans.eb(e);
    }
}

inline void solve() {
    int x, y, z;
    while (cin >> x >> y && x > 0 && y > 0) { 
        int st = 1;
        int m = 1, n = 0;
        cin >> z;
        if (z == 1) st = min(x, y);
        G[x].insert({z, y});
        G[y].insert({z, x});
        n = max({n, x, y});
        in[x]++, in[y]++;

        while (cin >> x >> y && x > 0 && y > 0) {
            cin >> z;
            if (z == 1) st = min(x, y);
            G[x].insert({z, y});
            G[y].insert({z, x});
            n = max({n, x, y});
            in[x]++, in[y]++;
            m++;
        }

        dfs(st);
        reverse(ALL(ans));
        int ok = 1;
        for (int i = 1; i <= n; i++) {
            if (in[i] % 2) ok = 0;
        }
        if (!ok || SZ(ans) != m) {
            cout << "Round trip does not exist\n";
        } else {
            for (int i : ans) cout << i << ' ';
            cout << '\n';
        }
        ans.clear();
        for (int i = 1; i <= n; i++) G[i].clear(), in[i] = 0;
        for (int i = 1; i <= m; i++) vis[i] = 0;
    }
}

signed main() {
	IO;	
	solve();	
}
