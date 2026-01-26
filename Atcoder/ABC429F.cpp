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

#define node array<int, 3>

const int mxN = 2e5 + 5;

struct Mat {
    vector<vector<int>> m;
    Mat(): m(3, vector<int>(3, inf)) {}
    Mat(const string &s): m(3, vector<int>(3, inf)) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (s[i] == '#' || s[j] == '#') m[i][j] = inf;
                else m[i][j] = abs(i - j);
            }
        }
        if (s != "...") m[0][2] = m[2][0] = inf;
    }

    Mat operator + (const Mat &rhs) {
        Mat res;
        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    ckmin(res.m[i][j], m[i][k] + rhs.m[k][j] + 1);
                }
            }
        }
        return res;
    }

    void print() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << m[i][j] << " \n"[j == 2];
            }
        }
    }
};


struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    int n;
    vector<Mat> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4) {}

    void up(int x) {
        seg[x] = seg[ls] + seg[rs];
    }

    void build(int l, int r, int x, vector<string> &a) {
        if(l == r) {
            seg[x] = Mat(a[l]);
            return;
        }
        build(l, mid, ls, a); build(mid+1, r, rs, a);
        up(x);
    }

    void modify(int p, string v, int l, int r, int x) {
        if(l == r) {
            seg[x] = Mat(v);
            return;
        }
        if(p <= mid) modify(p, v, l, mid, ls);
        else modify(p, v, mid+1, r, rs);
        up(x);
    }
    void modify(int p, string v) { modify(p, v, 0, n - 1, 1); }
};


inline void solve() {
    int n; cin >> n;
    string s[3];
    cin >> s[0] >> s[1] >> s[2];
    vector<string> p;
    for (int i = 0; i < n; i++) {
        string r = {s[0][i], s[1][i], s[2][i]};
        p.eb(r);
    }
    Segment_Tree seg(n);
    seg.build(0, n - 1, 1, p);

    int q; cin >> q;
    while (q--) {
        int r, c;
        cin >> c >> r;
        r--; c--;
        if (p[r][c] == '#') p[r][c] = '.';
        else if (p[r][c] == '.') p[r][c] = '#';
        seg.modify(r, p[r]);
        
        int res = seg.seg[1].m[0][2];
        //seg.seg[1].print();
        if (res >= inf) cout << -1 << '\n';
        else cout << res << '\n';
    }
}

signed main() {
    IO;	
    solve();	
}
