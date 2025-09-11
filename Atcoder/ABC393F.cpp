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

// lazytag segment tree
struct SegmentTree {
    int n;
    vector<int> seg, tag;
    SegmentTree(int _n): n(_n), seg(_n * 4), tag(_n * 4) {}

#define ls x<<1
#define rs (x<<1)|1
#define mid ((l+r)>>1)

    inline int op(const int &a, const int &b) {
        return max(a, b);
    }

    inline void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    inline void push_tag(int l, int r, int x, int v) {
        tag[x] = max(tag[x], v);	
        seg[x] = max(seg[x], tag[x]);
    }

    inline void down(int l, int r, int x) {
        if(!tag[x]) return;
        push_tag(l, mid, ls, tag[x]);
        push_tag(mid+1, r, rs, tag[x]);
        tag[x] = 0;
    }
    void build(vector<int> &a, int l, int r, int x = 1) {
        if(l == r) {
            seg[x] = a[l];
            return;
        }
        build(a, l, mid, ls);	build(a, mid+1, r, rs);
        up(x);
    } 
    void build(vector<int> &a) { build(a, 0, n, 1); }

    void modify(int a, int b, int v, int l, int r, int x = 1) {
        if(a <= l and r <= b) {
            push_tag(l, r, x, v);
            return;
        }
        if (l != r) down(l, r, x);
        if(a <= mid) modify(a, b, v, l, mid, ls);
        if(b > mid) modify(a, b, v, mid+1, r, rs);
        up(x);
    }
    void modify(int a, int b, int v) { modify(a, b, v, 0, n, 1); }

    int query(int a, int b, int l, int r, int x = 1) {
        if (l != r) down(l, r, x);
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs));
        return res;
    }
    int query(int a, int b) { return query(a, b, 0, n, 1); }
};

inline void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> tmp;
    for (int &i : a) { 
        cin >> i;
        tmp.eb(i);
    }
    vector<vector<pii>> qry(n + 1);
    for (int i = 0; i < q; i++) {
        int r, x;
        cin >> r >> x;
        qry[r - 1].eb(x, i);
        tmp.eb(x);
    }

    sort(ALL(tmp));
    uni(tmp);

    SegmentTree seg(SZ(tmp) + 5);
    vector<int> ans(q);
    for (int i = 0; i < n; i++) {
        int ai = lb(tmp, a[i]) - tmp.begin() + 1;
        int mx = seg.query(0, ai - 1);
        seg.modify(ai, SZ(tmp), mx + 1);
        for (auto [x, idx] : qry[i]) {
            int xi = lb(tmp, x) - tmp.begin() + 1;
            ans[idx] = seg.query(0, xi);
        }
    }
    for (int i : ans) cout << i << '\n';
}

signed main() {
	IO;	
	solve();	
}
