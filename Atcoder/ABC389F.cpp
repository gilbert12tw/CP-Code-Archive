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
        tag[x] += v;	
        seg[x] += v;
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

    int findl(int val, int l, int r, int x = 1) {
        if (l == r) return l;
        if (l != r) down(l, r, x);
        if (seg[ls] >= val) return findl(val, l, mid, ls);
        return findl(val, mid + 1, r, rs);
    }
    int findl(int val) { return findl(val, 0, n, 1); }

    int findr(int val) { return findl(val + 1, 0, n, 1) - 1; }
};

inline void solve() {
    int n, q;
    cin >> n;

    SegmentTree seg(500005);
    vector<int> a(500001);
    iota(ALL(a), 0);
    seg.build(a);

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;

        int ql = seg.findl(l);

        int qr = seg.findr(r);

        test(ql, qr);
        seg.modify(ql, qr, 1);
    }

    cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << seg.query(x, x) << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
