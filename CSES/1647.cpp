#include<bits/stdc++.h>
//#define loli
using namespace std;
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

int n, q, a[mxN], nxt_smaller[mxN];
int pa[mxN], rk[mxN];
int ans[mxN];
vector<pii> qry[mxN];
vector<int> edge[mxN];

int get(int x) {
    return (x == pa[x] ? x : (pa[x] = get(pa[x])));
}

inline void onion(int u, int v) {
    u = get(u); v = get(v);
    if (u == v) return;
    if (rk[u] > rk[v]) {
        a[u] = a[v];
        pa[v] = u; 
    } else {
        if (rk[u] == rk[v]) rk[v]++;
        pa[u] = v;
    }
}

inline void solve() {
    cin >> n >> q;
    vector<int> stk;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pa[i] = i;
    }
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qry[r].eb(l, i);
    }

    stk.eb(0);
    for (int i = n; i >= 1; i--) {
        while (SZ(stk) > 1 && a[stk.back()] >= a[i]) stk.pop_back();
        nxt_smaller[i] = stk.back();
        if (nxt_smaller[i]) edge[nxt_smaller[i]].eb(i);
        stk.eb(i);
    }

    for (int i = 1; i <= n; i++) {
        for (int j : edge[i]) {
            onion(j, i);
        }
        for (auto [l, id] : qry[i]) {
            ans[id] = a[get(l)];
        }
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
}

signed main() {
	IO;	
	solve();	
}
