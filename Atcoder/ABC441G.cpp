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
template <typename... T> void _print(T... args) {
    ((cerr << args << ' '), ...);
    cerr << '\n';
}
#ifdef debug
#define test(args...) _print("[" + string(#args) + "]:", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 2e5 + 5;

int n, q;

struct Node {
    int up = 0, dn = 0, mx = 0;
    int flip = 0, tag = 0; // flip: 0/1, tag: add val
    bool clr = false;      // clr: reset to 0
};

#define ls (id<<1)
#define rs ((id<<1)|1)
#define mid ((l+r)>>1)

Node seg[mxN * 4];

void up(int id) {
    seg[id].up = seg[ls].up + seg[rs].up;
    seg[id].dn = seg[ls].dn + seg[rs].dn;
    seg[id].mx = max(seg[ls].mx, seg[rs].mx);
}

void do_add(int id, int val) {
    if (seg[id].up > 0) seg[id].mx += val;
    seg[id].tag += val;
}

void do_clr(int id) {
    seg[id].mx = 0;
    seg[id].tag = 0;
    seg[id].clr = true;
}

void do_flip(int id) {
    swap(seg[id].up, seg[id].dn);
    seg[id].flip ^= 1;
}

void down(int id) {
    if (seg[id].clr) {
        do_clr(ls);
        do_clr(rs);
        seg[id].clr = false;
    }
    
    if (seg[id].flip) {
        do_flip(ls);
        do_flip(rs);
        seg[id].flip = 0;
    }
    
    if (seg[id].tag != 0) {
        do_add(ls, seg[id].tag);
        do_add(rs, seg[id].tag);
        seg[id].tag = 0;
    }
}

void build(int l = 1, int r = n, int id = 1) {
    seg[id].tag = 0;
    seg[id].flip = 0;
    seg[id].clr = false;
    if (l == r) {
        seg[id].up = 1;
        seg[id].dn = 0;
        seg[id].mx = 0;
        return;
    }
    build(l, mid, ls);
    build(mid+1, r, rs);
    up(id);
}

// Type 1: Add X
void place(int a, int b, int val, int l = 1, int r = n, int id = 1) {
    if (l > b || r < a) return;
    if (a <= l && r <= b) {
        do_add(id, val);
        return;
    }
    down(id);
    place(a, b, val, l, mid, ls);
    place(a, b, val, mid+1, r, rs);
    up(id);
}

// Type 2: Eat & Flip
void eat_and_flip(int a, int b, int l = 1, int r = n, int id = 1) {
    if (l > b || r < a) return;
    if (a <= l && r <= b) {
        do_clr(id);  
        do_flip(id);
        return;
    }
    down(id);
    eat_and_flip(a, b, l, mid, ls);
    eat_and_flip(a, b, mid+1, r, rs);
    up(id);
}

// Type 3: Query Max
int query(int a, int b, int l = 1, int r = n, int id = 1) {
    if (l > b || r < a) return 0;
    if (a <= l && r <= b) return seg[id].mx;
    down(id);
    return max(query(a, b, l, mid, ls), query(a, b, mid+1, r, rs));
}

inline void solve() {
    cin >> n >> q;
    build();
    while(q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            place(l, r, x);
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            eat_and_flip(l, r);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(l, r) << "\n";
        }
    }
}

signed main() {
    IO; 
    solve();    
}
