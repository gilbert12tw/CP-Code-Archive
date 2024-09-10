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

// Lazytag segment tree
struct SegmentTree {
    int n;
    vector<pii> seg;
    vector<int> tag;
    SegmentTree(int _n): n(_n), seg((_n + 1) * 4), tag((_n + 1) * 4) {}

#define ls (x<<1)
#define rs ((x<<1)|1LL)
#define mid ((l+r)>>1)

    inline pii op(pii a, pii b) {
        return max(a, b);
    }

    inline void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    inline void push_tag(int l, int r, int x, int v) {
        if (l == r) seg[x].S = l;
        tag[x] += v;	
        seg[x].F += v;
    }

    inline void down(int l, int r, int x) {
        if (l >= r) return;
        if(!tag[x]) return;
        push_tag(l, mid, ls, tag[x]);
        push_tag(mid+1, r, rs, tag[x]);
        tag[x] = 0;
    }

    void modify(int a, int b, int v, int l, int r, int x = 1) {
        if(a <= l and r <= b) {
            push_tag(l, r, x, v);
            down(l, r, x);
            return;
        }
        if (l != r) down(l, r, x);
        if(a <= mid) modify(a, b, v, l, mid, ls);
        if(b > mid) modify(a, b, v, mid+1, r, rs);
        up(x);
    }
    void modify(int a, int b, int v) { modify(a, b, v, 1, n, 1); }
};

inline void solve() {
    int n;
    cin >> n;
    vector<vector<pii>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; 
        cin >> u >> v >> w;
        g[u].eb(v, w);
        g[v].eb(u, w);
    }

    vector<int> pa(n + 1), pa_weigth(n + 1), dis(n + 1), in(n + 1), out(n + 1), pos(n + 1);
    int aimer = 0;
    function<void(int, int, int)> dfs = [&](int u, int p, int sum) {
        dis[u] = sum;
        in[u] = ++aimer;
        pos[aimer] = u;
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            pa[v] = u;
            pa_weigth[v] = w;
            dfs(v, u, sum + w);
        }
        out[u] = aimer;
    };

    dfs(1, 0, 0);
    SegmentTree seg(n);

    for (int u = 1; u <= n; u++) {
        seg.modify(in[u], in[u], dis[u]);
    }

    vector<int> del(n + 1);
    int ans = 0;
    for (int k = 1; k <= n; k++) {
        auto [len, u] = seg.seg[1];
        u = pos[u];
        ans += len * 2; 
        cout << ans << '\n';
        // Del u
        while (u != 1 && !del[u]) {
            del[u] = 1;
            test(k, u, in[u], out[u], pa_weigth[u]);
            seg.modify(in[u], out[u], -pa_weigth[u]);
            u = pa[u];
        }
    }
}

signed main() {
	IO;	
	solve();	
}
