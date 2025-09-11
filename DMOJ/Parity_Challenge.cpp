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


struct Node {
    bool has_ad = 0, nxtopt = 0; // 0->+,  1->x
    bool pre_sum = 0, suf_sum = 0, sum = 0;
};

struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    int n;
    vector<Node> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4) {}

    inline Node op(const Node &a, const Node &b) {
        Node res;
        if (a.nxtopt == 0) { // +
            res.sum = (a.sum ^ b.sum);
            if (a.has_ad) res.pre_sum = a.pre_sum;
            else res.pre_sum = a.sum;
            if (b.has_ad) res.suf_sum = b.suf_sum;
            else res.suf_sum = b.sum;
            res.nxtopt = b.nxtopt;
            res.has_ad = 1;
        } else { // x
            res.sum = a.sum ^ a.suf_sum ^ b.sum ^ b.pre_sum ^ (a.suf_sum & b.pre_sum);
            if (a.has_ad) res.pre_sum = a.pre_sum;
            else res.pre_sum = a.sum & b.pre_sum;
            if (b.has_ad) res.suf_sum = b.suf_sum;
            else res.suf_sum = b.sum & a.suf_sum;
            res.has_ad = (b.has_ad | a.has_ad);
            res.nxtopt = b.nxtopt;
        }
        return res;
    }

    void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    void build(int l, int r, int x, vector<int> &a, string &s) {
        if(l == r) {
            seg[x] = (Node){0, s[l] != '+', a[l] % 2, a[l] % 2, a[l] % 2};
            return;
        }
        build(l, mid, ls, a, s); build(mid+1, r, rs, a, s);
        up(x);
    }
    void build(vector<int> &a, string &s) { build(0, n - 1, 1, a, s); }

    void modify(int p, int type, int l, int r, int x) {
        if(l == r) {
            int t = seg[x].sum;
            if (!type) seg[x].pre_sum = seg[x].suf_sum = seg[x].sum = (t ^ 1);
            else seg[x].nxtopt ^= 1;
            return;
        }
        if(p <= mid) modify(p, type, l, mid, ls);
        else modify(p, type, mid+1, r, rs);
        up(x);
    }
    void modify(int p, int type) { modify(p, type, 0, n - 1, 1); }

    Node query(int a, int b, int l, int r, int x) {
        if (b < a) return (Node){0, 0, 0, 0, 0};
        if(a <= l and r <= b) return seg[x];
        if (a <= mid && b > mid) return op(query(a, b, l, mid, ls), query(a, b, mid+1, r, rs));
        if(a <= mid) return query(a, b, l, mid, ls);
        return query(a, b, mid+1, r, rs);
    }
    Node query(int a, int b) { return query(a, b, 0, n - 1, 1); }
};

inline void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    string opt;
    for (int &i : a) cin >> i;
    cin >> opt;
    opt.push_back('+');

    Segment_Tree seg(n);
    seg.build(a, opt);
    for (int i = 0; i < q; i++) {
        char op;
        int l, r, x;
        cin >> op;
        if (op == 'Q') {
            cin >> l >> r; l--; r--;
            int ans;
            if (r == n - 1) {
                Node mm = seg.query(l, r); mm.has_ad = 0;
                mm.pre_sum = mm.suf_sum = mm.sum;
                ans = seg.op(seg.query(0, l - 1), mm).sum;
            } else {
                Node mm = seg.query(l, r); mm.has_ad = 0;
                mm.pre_sum = mm.suf_sum = mm.sum;
                ans = seg.op(seg.op(seg.query(0, l - 1), mm), seg.query(r + 1, n - 1)).sum;
            }
            //int pre = seg.op(seg.op(seg.query(0, l - 1), seg.query(l, r)), seg.query(r + 1, n - 1)).pre_sum;
            //int suf = seg.op(seg.op(seg.query(0, l - 1), seg.query(l, r)), seg.query(r + 1, n - 1)).suf_sum;
            //test(ans, pre, suf);
            cout << (ans ? "odd" : "even") << '\n';
        } else {
            cin >> x; x--;
            seg.modify(x, op == 'O');
        }
    }
}

signed main() {
	IO;	
	solve();	
}
