#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int, int>
#define f first
#define s second
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define IO ios_base::sync_with_stdio(0);cin.tie(0);

const ll INF = 1000000000000000000;
const ll NINF = -INF;
const ll MAXR = 1000000001;
const int MAXN = 100000 + 5;

int n;
ll W[MAXN], A[MAXN], dp[MAXN];

struct LiChao {
    struct Line {
        ll m, b;
        Line(ll _m = 0, ll _b = NINF) : m(_m), b(_b) {}
    };
    struct Node {
        Line ln;
        Node *l, *r;
        Node(Line _ln) : ln(_ln), l(nullptr), r(nullptr) {}
    };
    ll lo, hi;
    Node* root;
    LiChao(ll _lo, ll _hi) : lo(_lo), hi(_hi), root(nullptr) {}
    ll eval(const Line& ln, ll x) const { return ln.m * x + ln.b; }
    void insert_line(Line nw) { insert_line(root, lo, hi, nw); }
    void insert_line(Node*& nd, ll l, ll r, Line nw) {
        if (!nd) {
            nd = new Node(nw);
            return;
        }
        ll mid = (l + r) >> 1;
        bool lef = eval(nw, l) > eval(nd->ln, l);
        bool md = eval(nw, mid) > eval(nd->ln, mid);
        if (md) swap(nw, nd->ln);
        if (r - l == 1) return;
        if (lef != md)
            insert_line(nd->l, l, mid, nw);
        else
            insert_line(nd->r, mid, r, nw);
    }
    ll query(ll x) const { return query(root, lo, hi, x); }
    ll query(Node* nd, ll l, ll r, ll x) const {
        if (!nd) return NINF;
        ll res = eval(nd->ln, x);
        if (r - l == 1) return res;
        ll mid = (l + r) >> 1;
        if (x < mid)
            return max(res, query(nd->l, l, mid, x));
        else
            return max(res, query(nd->r, mid, r, x));
    }
};

struct CentroidTree {
    vector<vector<pair<int, int>>> tree;
    vector<bool> removed;
    vector<int> sz;
    CentroidTree(int _n) : tree(_n + 1), removed(_n + 1), sz(_n + 1) {}

    void add_edge(int u, int v, int w) {
        tree[u].pb({v, w});
        tree[v].pb({u, w});
    }

    void get_sz(int u, int p) {
        sz[u] = 1;
        for (auto& e : tree[u]) {
            int v = e.f;
            if (v == p || removed[v]) continue;
            get_sz(v, u);
            sz[u] += sz[v];
        }
    }

    int get_centroid(int u, int p, int tot) {
        for (auto& e : tree[u]) {
            int v = e.f;
            if (v != p && !removed[v] && sz[v] > tot / 2)
                return get_centroid(v, u, tot);
        }
        return u;
    }

    void collect(int u, int p, ll d, vector<pair<int, ll>>& vec) {
        vec.pb({u, d});
        for (auto& e : tree[u]) {
            int v = e.f, w = e.s;
            if (v == p || removed[v]) continue;
            collect(v, u, d + w, vec);
        }
    }

    void decompose(int u) {
        get_sz(u, -1);
        int c = get_centroid(u, -1, sz[u]);
        removed[c] = true;
        vector<vector<pair<int, ll>>> groups;
        for (auto& e : tree[c]) {
            int v = e.f, w = e.s;
            if (removed[v]) continue;
            vector<pair<int, ll>> vec;
            collect(v, c, w, vec);
            groups.pb(move(vec));
        }

        LiChao lf(0, MAXR), lb(0, MAXR);
        lf.insert_line({W[c], A[c]});
        dp[c] = max(dp[c], A[c]);
        for (auto& grp : groups) {
            for (auto& pr : grp) {
                int x = pr.f;
                ll d = pr.s;
                dp[x] = max(dp[x], lf.query(d));
            }
            for (auto& pr : grp) {
                int y = pr.f;
                ll d = pr.s;
                lf.insert_line({W[y], A[y] + W[y] * d});
            }
        }
        dp[c] = max(dp[c], lf.query(0));

        lb.insert_line({W[c], A[c]});
        for (int i = SZ(groups) - 1; i >= 0; --i) {
            auto& grp = groups[i];
            for (auto& pr : grp) {
                int x = pr.f;
                ll d = pr.s;
                dp[x] = max(dp[x], lb.query(d));
            }
            for (auto& pr : grp) {
                int y = pr.f;
                ll d = pr.s;
                lb.insert_line({W[y], A[y] + W[y] * d});
            }
        }

        for (auto& e : tree[c]) {
            int v = e.f;
            if (!removed[v]) decompose(v);
        }
    }
};

inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> W[i];
    for (int i = 1; i <= n; i++) cin >> A[i];
    CentroidTree cd(n);
    for (int i = 1; i < n; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        cd.add_edge(u, v, l);
    }
    for (int i = 1; i <= n; i++) dp[i] = NINF;
    cd.decompose(1);
    ll ans = INF;
    for (int i = 1; i <= n; i++) ans = min(ans, dp[i]);
    cout << ans;
}

signed main() {
    IO;
    solve();
    return 0;
}
