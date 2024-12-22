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

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }


// dynamic lazytag segment tree
struct SegmentTree {
    int n, tot, root;
    vector<int> seg, ls, rs;
    vector<pii> tag;
    SegmentTree(int _n): n(_n), tot(0), root(0), seg(_n * 25), ls(_n * 25), rs(_n * 25), tag(_n * 25) {}

#define mid ((l+r)>>1)

    inline int op(const int &a, const int &b) {
        return max(a, b);
    }

    inline void up(int x) {
        seg[x] = op(seg[ls[x]], seg[rs[x]]);
    }

    inline void push_tag(int l, int r, int x, pii v) {
        if (tag[x] == pii(0, 0) || tag[x].first - tag[x].second < v.first - v.second)
            tag[x] = v;
        seg[x] = max(seg[x], tag[x].first + r - tag[x].second + 1);
    }

    inline void down(int l, int r, int x) {
        if (tag[x].first == 0 && tag[x].second == 0) return;
        if (!ls[x]) ls[x] = ++tot;
        if (!rs[x]) rs[x] = ++tot;
        push_tag(l, mid, ls[x], tag[x]);
        push_tag(mid+1, r, rs[x], tag[x]);
        tag[x] = mkp(0, 0);
    }

    void modify(int a, int b, pii v, int l, int r, int &x) {
        if (x == 0) x = ++tot;
        if (l != r) down(l, r, x);
        if(a <= l and r <= b) {
            push_tag(l, r, x, v);
            return;
        }
        if(a <= mid) modify(a, b, v, l, mid, ls[x]);
        if(b > mid) modify(a, b, v, mid+1, r, rs[x]);
        up(x);
    }
    void modify(int a, int b, pii v) { modify(a, b, v, 1, 1e9, root); }

    int query(int a, int b, int l, int r, int &x) {
        if (r < l || b < a) return 0;
        if (!x) return 0;
        if (l != r) down(l, r, x);
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls[x]);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs[x]));
        return res;
    }
    int query(int a, int b) { return query(a, b, 1, 1e9, root); }
};

inline void solve() {
    int n; cin >> n;
    SegmentTree seg(1e6 + 5);
    while (n--) {
        int l, r;
        cin >> l >> r;
        int x = seg.query(1, l - 1);
        seg.modify(l, r, mkp(x, l));
    }
    cout << seg.query(1, 1e9) << '\n';
}

/*
2 
1 10
5 15
*/

signed main() {
	IO;	
	solve();	
}
