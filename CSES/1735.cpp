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
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }


// lazytag segment tree
struct SegmentTree {
    int n;
    vector<int> seg, tag, set_tag;

    SegmentTree(int _n) {
        n = _n;
        seg.resize(n * 4);
        tag.resize(n * 4);
        set_tag.resize(n * 4);
    }

#define ls x<<1
#define rs (x<<1)|1
#define mid ((l+r)>>1)

    inline void up(int x) {
        seg[x] = seg[ls] + seg[rs];
    }

    inline void push_tag(int l, int r, int x, int v) {
        if (v < 0) { // set
            v = -v;
            tag[x] = 0;
            set_tag[x] = v;
            seg[x] = v * (r - l + 1);
        } else { // add 
            tag[x] += v;	
            seg[x] += v * (r - l + 1);
        }
    }

    inline void down(int l, int r, int x) {
        if (set_tag[x]) {
            push_tag(l, mid, ls, -set_tag[x]);
            push_tag(mid+1, r, rs, -set_tag[x]);
            set_tag[x] = 0;
        }
        if (tag[x]) {
            push_tag(l, mid, ls, tag[x]);
            push_tag(mid+1, r, rs, tag[x]);
            tag[x] = 0;
        }
    }

    void build(vector<int> &a, int l, int r, int x = 1) {
        if(l == r) {
            seg[x] = a[l];
            return;
        }
        build(a, l, mid, ls);	build(a, mid+1, r, rs);
        up(x);
    } 
    void build(vector<int> &a) { build(a, 1, n, 1); }

    void modify(int a, int b, int v, int l, int r, int x = 1) {
        if (l != r) down(l, r, x);
        if(a <= l and r <= b) {
            push_tag(l, r, x, v);
            return;
        }
        if(a <= mid) modify(a, b, v, l, mid, ls);
        if(b > mid) modify(a, b, v, mid+1, r, rs);
        up(x);
    }
    void modify(int a, int b, int v) { modify(a, b, v, 1, n, 1); }

    int query(int a, int b, int l, int r, int x = 1) {
        if (l != r) down(l, r, x);
        if(a <= l && r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res += query(a, b, mid+1, r, rs);
        return res;
    }
    int query(int a, int b) { return query(a, b, 1, n, 1); }
};

inline void solve() {
    int n, q; cin >> n >> q;
    SegmentTree segment(n);

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    segment.build(a);

    while (q--) {
        int opt, l, r, v;
        cin >> opt >> l >> r;
        if (opt == 3) {
            cout << segment.query(l, r) << '\n';
        } else {
            cin >> v;
            if (opt == 2) v = -v;
            segment.modify(l, r, v);
        }
    }
}

signed main() {
    IO;	
    solve();	
}
