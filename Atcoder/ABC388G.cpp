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

struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    int n;
    vector<int> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4) {}

    inline int op(const int &a, const int &b) {
        return max(a, b);
    }

    void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    void build(int l, int r, int x, vector<int> &a) {
        if(l == r) {
            seg[x] = a[l] - l;
            return;
        }
        build(l, mid, ls, a); build(mid+1, r, rs, a);
        up(x);
    }

    int query(int a, int b, int l, int r, int x) {
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs));
        return res;
    }
    int query(int a, int b) { return query(a, b, 0, n, 1); }
};

inline void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;

    Segment_Tree seg(n);
    vector<int> nxt(n + 1);
    nxt[n] = 2 * n;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < n && a[j] < 2 * a[i]) j++;
        nxt[i] = j;
    }

    seg.build(0, n, 1, nxt);

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        l--, r--;
        int a = l, b = r;
        r++;
        while (l < r) {
            int mm = (l + r + 1) >> 1;
            int mx = seg.query(a, mm - 1);
            int val = mm - 1 + max(mx, mm - a);
            if (val <= b) l = mm;
            else r = mm - 1;
        }
        cout << l - a << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
