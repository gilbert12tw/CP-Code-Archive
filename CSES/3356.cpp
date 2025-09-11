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
    vector<pii> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4, mkp(-inf, inf)) {}

    inline pii op(const pii &a, const pii &b) {
        return mkp(max(a.f, b.f), min(a.s, b.s));
    }

    void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    void modify(int p, pii v, int l, int r, int x) {
        if(l == r) {
            seg[x] = v;
            return;
        }
        if(p <= mid) modify(p, v, l, mid, ls);
        else modify(p, v, mid+1, r, rs);
        up(x);
    }
    void modify(int p, pii v) { modify(p, v, 0, n, 1); }

    pii query(int a, int b, int l, int r, int x) {
        if(a <= l and r <= b) return seg[x];
        pii res(-inf, inf);
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs));
        return res;
    }
    pii query(int a, int b) { return query(a, b, 0, n , 1); }
};

inline void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &i : a) cin >> i;

    unordered_map<int, set<int>> mp;
    mp.reserve(1000000);
    for (int i = 0; i < n; i++) {
        mp[a[i]].insert(i);
    }

    auto find_next = [](const set<int> &s, int pos) -> int {
        auto it = s.upper_bound(pos);
        if (it == s.end()) return inf;
        return *it;
    };
    auto find_prev = [](const set<int> &s, int pos) -> int {
        auto it = s.lower_bound(pos);
        if (it == s.begin()) return -inf;
        return *prev(it);
    };

    Segment_Tree seg(n + 1);
    auto update = [&](int x) -> void {
        seg.modify(x, mkp(find_prev(mp[a[x]], x), find_next(mp[a[x]], x)));
    };
    for (int i = 0; i < n; i++) {
        update(i);
    }

    unordered_set<int> tbd;
    while (q--) {
        int o, x, y;
        cin >> o >> x >> y;
        if (o == 1) {
            x--;
            tbd.insert(x);
            tbd.insert(find_prev(mp[a[x]], x));
            tbd.insert(find_next(mp[a[x]], x));
            mp[a[x]].erase(x);
            a[x] = y;
            mp[a[x]].insert(x);
            tbd.insert(find_prev(mp[a[x]], x));
            tbd.insert(find_next(mp[a[x]], x));
        } else {
            for (int i : tbd) if (i >= 0 && i < n) {
                update(i);
            }
            tbd.clear();

            x--; y--;
            pii res = seg.query(x, y);
            if (res.f >= x || res.s <= y) cout << "NO\n";
            else cout << "YES\n";
        }
    }
}

signed main() {
	IO;	
	solve();	
}
