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

const int mxN = 2e5 + 5;

int n, m, k;

struct DSU {
    int cc;
	int pa[mxN], sz[mxN];
	vector<pii> stk;
	void init(int n) {
        cc = n;
		for (int i = 0; i <= n; i++) pa[i] = i, sz[i] = 1; 
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
        cc--;
		return 1;
	}

	int record() { return (int)(stk.size()); }

	void roll_back(int keep_point) {
		while (SZ(stk) > keep_point) {
			pa[stk.back().F] = stk.back().F;
			sz[stk.back().S] -= sz[stk.back().F];
			stk.pop_back();
            cc++;
		}
	}
} dsu;

vector<pii> seg[mxN * 4];

#define ls (x<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
void add(pii e, int ql, int qr, int l = 0, int r = k, int x = 1) {
    if (ql <= l && r <= qr) {
        seg[x].eb(e);
        return;
    }
    if (ql <= mid) add(e, ql, qr, l, mid, ls);
    if (qr > mid) add(e, ql, qr, mid+1, r, rs);
}

void dfs(int l = 0, int r = k, int x = 1) {
    int kp = dsu.record();
    for (auto [u, v] : seg[x]) { 
        dsu.merge(u, v);
    }

    if (l == r) {
        cout << n - SZ(dsu.stk) << ' ';
    } else {
        dfs(l, mid, ls);
        dfs(mid+1, r, rs);
    }

    dsu.roll_back(kp);
}

inline void solve() {
    cin >> n >> m >> k;
    map<pii, int> mp;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        mp[mkp(u, v)] = 0;
    }
    for (int i = 1; i <= k; i++) {
        int op, u, v;
        cin >> op >> u >> v;
        if (u > v) swap(u, v);
        if (op == 1) {
            mp[mkp(u, v)] = i;
        } else {
            add(mkp(u, v), mp[mkp(u, v)], i - 1);
            mp.erase(mkp(u, v));
        }
    }
    for (auto [e, t] : mp) {
        add(e, t, k);
    }

    dsu.init(n);
    dfs();
}

signed main() {
	IO;	
	solve();	
}
