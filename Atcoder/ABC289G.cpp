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
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 2e5 + 5;

int n, m;

class LC_tree {
private:
    struct Line {
        pii line;
        int ls = 0, rs = 0;
    } seg[mxN * 15];
    inline int cal(pii l, int x) {
        return l.first * x + l.second;
    }
    int tot = 0;
public:
    void insert(pii t, int &id, int l, int r) {
        if (id == 0) id = ++tot;
        int mid = (l+r) >> 1;
        if (cal(t, mid) > cal(seg[id].line, mid)) swap(t, seg[id].line);
        if (l == r)  return;
        if (cal(t, l) > cal(seg[id].line, l)) insert(t, seg[id].ls, l, mid);
        if (cal(t, r) > cal(seg[id].line, r)) insert(t, seg[id].rs, mid+1, r);
    }

    int query(int p, int id, int l, int r) {
        if (id == 0) return -INF;
        if (l == r) return cal(seg[id].line, p);
        int mid = (l+r)>>1;
        if (p <= mid) return max(query(p, seg[id].ls, l, mid), cal(seg[id].line, p));
        else return max(query(p, seg[id].rs, mid+1, r), cal(seg[id].line, p));
    }
} LCT;

int b[mxN], c[mxN];

inline void solve() {
    cin >> n >> m;
    int mx = 0;
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < m; i++) cin >> c[i], mx = max(mx, c[i]);

    int root = 0;
    sort(b, b + n, greater<int>());
    for (int i = 0; i < n; i++) {
        LCT.insert({(i + 1), (i + 1) * b[i]}, root, 0, mx);
    }

    for (int i = 0; i < m; i++) cout << LCT.query(c[i], root, 0, mx) << ' ';
}

signed main() {
	IO;	
	solve();	
}
