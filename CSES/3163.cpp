#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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

struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    int n;
    vector<int> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4) {}

    inline int op(const int &a, const int &b) {
        return a + b;
    }

    void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    void build(int l, int r, int x, vector<int> &a) {
        if(l == r) {
            seg[x] = a[l];
            return;
        }
        build(l, mid, ls, a); build(mid+1, r, rs, a);
        up(x);
    }

    void modify(int p, int v, int l, int r, int x) {
        if(l == r) {
            seg[x] += v;
            return;
        }
        if(p <= mid) modify(p, v, l, mid, ls);
        else modify(p, v, mid+1, r, rs);
        up(x);
    }
    void modify(int p, int v) { modify(p, v, 0, n, 1); }

    int query(int a, int b, int l, int r, int x) {
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs));
        return res;
    }
    int query(int a, int b) { return query(a, b, 0, n , 1); }
};

struct Query {
    int lo = 0, hi = 0, id = -1, type = -1;
};

inline void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), tmp;
    for (int &i : a) {
        cin >> i;
        tmp.eb(i);
    }

    vector<vector<Query>> qry(n + 1);
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        qry[a - 1].eb((Query){c, d, i, 0});
        qry[b].eb((Query){c, d, i, 1});
        tmp.eb(c); tmp.eb(d);
    }
    sort(ALL(tmp));
    uni(tmp);

    Segment_Tree seg(SZ(tmp) + 1);
    vector<int> ans(q);
    for (int i = 1; i <= n; i++) {
        a[i-1] = lb(tmp, a[i-1]) - tmp.begin();
        seg.modify(a[i-1], 1);
        for (auto [lo, hi, id, type] : qry[i]) {
            lo = lb(tmp, lo) - tmp.begin();
            hi = lb(tmp, hi) - tmp.begin();
            ans[id] += (seg.query(lo, hi) * (type ? 1 : -1)); 
        }
    }
    for (int i : ans) cout << i << '\n';
}

signed main() {
	IO;	
	solve();	
}
