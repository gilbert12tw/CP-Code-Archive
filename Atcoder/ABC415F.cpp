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

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

struct Node {
    int ans, pref_len, suff_len;
    char pref_char, suff_char;
    int len;

    Node() : ans(0), pref_len(0), suff_len(0), pref_char('\0'), suff_char('\0'), len(0) {}
};


struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)

    int n;
    vector<Node> seg;
    string& s_ref;

    Segment_Tree(int _n, string& s): n(_n), seg(_n * 4 + 5), s_ref(s) {}

    inline Node op(const Node &a, const Node &b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.pref_char = a.pref_char;
        res.suff_char = b.suff_char;

        res.ans = max(a.ans, b.ans);
        if (a.suff_char == b.pref_char) {
            ckmax(res.ans, a.suff_len + b.pref_len);
        }

        res.pref_len = a.pref_len;
        if (a.pref_len == a.len && a.suff_char == b.pref_char) {
            res.pref_len += b.pref_len;
        }

        res.suff_len = b.suff_len;
        if (b.suff_len == b.len && a.suff_char == b.pref_char) {
            res.suff_len += a.suff_len;
        }
        
        return res;
    }

    void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    void build(int l, int r, int x) {
        if(l == r) {
            seg[x].ans = 1;
            seg[x].pref_len = 1;
            seg[x].suff_len = 1;
            seg[x].pref_char = s_ref[l-1]; 
            seg[x].suff_char = s_ref[l-1];
            seg[x].len = 1;
            return;
        }
        build(l, mid, ls);
        build(mid+1, r, rs);
        up(x);
    }

    void modify(int p, char v, int l, int r, int x) {
        if(l == r) {
            seg[x].pref_char = v;
            seg[x].suff_char = v;
            return;
        }
        if(p <= mid) modify(p, v, l, mid, ls);
        else modify(p, v, mid+1, r, rs);
        up(x);
    }
    void modify(int p, char v) { modify(p, v, 1, n, 1); }

    Node query(int a, int b, int l, int r, int x) {
        if(a <= l && r <= b) return seg[x];
        
        bool left_queried = false;
        Node left_res, right_res;

        if (a <= mid) {
            left_res = query(a, b, l, mid, ls);
            left_queried = true;
        }
        if (b > mid) {
            right_res = query(a, b, mid+1, r, rs);
            if (left_queried) {
                return op(left_res, right_res);
            } else {
                return right_res;
            }
        }
        return left_res;
    }
    Node query(int a, int b) { return query(a, b, 1, n, 1); }
};

inline void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    Segment_Tree st(n, s);
    st.build(1, n, 1);

    for (int k = 0; k < q; ++k) {
        int type;
        cin >> type;
        if (type == 1) {
            int i; char c;
            cin >> i >> c;
            s[i-1] = c;
            st.modify(i, c);
        } else {
            int l, r;
            cin >> l >> r;
            Node result = st.query(l, r);
            cout << result.ans << '\n';
        }
    }
}

signed main() {
	IO;	
	solve();	
}

