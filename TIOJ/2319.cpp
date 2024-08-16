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
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }


int ans = 0;
const int mxN = 2e5 + 5;
int a[mxN];
set<pii> que;
struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    int n;
    vector<vector<int>> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4) {}

    void add(int a, int b, int v, int l, int r, int x) {
        if(a <= l && r <= b) {
            seg[x].eb(v);
            return;
        }
        if (a <= mid) add(a, b, v, l, mid, ls);
        if (b > mid)  add(a, b, v, mid+1, r, rs);
    }

    void query(int pos, int l, int r, int x) {
        for (int i : seg[x]) {
            if (a[i] < a[pos]) {
                ans += a[pos] - a[i];
                if (que.count(mkp(a[i], i))) {
                    que.erase(mkp(a[i], i));
                    que.insert(mkp(a[pos], i));
                }
                a[i] = a[pos]; 
            }
        }
        seg[x].clear();
        if (l == r) return;
        if(pos <= mid) query(pos, l, mid, ls);
        else query(pos, mid+1, r, rs);
    }
};

inline void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    Segment_Tree seg(n + 1);
    for (int i = 1; i <= n; i++) {
        int l, r; cin >> l >> r;
        seg.add(l, r, i, 1, n, 1);
    }
    for (int i = 1; i <= n; i++) {
        que.insert(mkp(a[i], i));
    }
    while (!que.empty()) {
        auto p = *prev(que.end());
        que.erase(prev(que.end()));
        seg.query(p.second, 1, n, 1);
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; i++) 
        cout << a[i] << ' ';
}

signed main() {
	IO;	
	solve();	
}
