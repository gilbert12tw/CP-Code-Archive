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

const int mxN = 3e6 + 5;

#define ls x<<1
#define rs x<<1|1
#define mid ((l+r)>>1)

int seg[mxN * 4], tag[mxN * 4];
void up(int x, int l, int r) {
    if (tag[x]) {
        seg[x] = (r - l + 1);
    } else {
        seg[x] = seg[ls] + seg[rs];
    }
}

void modify(int a, int b, int v, int l = -1000000, int r = 1000000, int x = 1) {
    if (a <= l && r <= b) {
        tag[x] += v;
        up(x, l, r);
        return;
    }
    if (a <= mid) modify(a, b, v, l, mid, ls);
    if (b > mid) modify(a, b, v, mid+1 ,r, rs);
    up(x, l, r);
}

struct line {
    int l, r, add;
    line (int _l, int _r, int _a)  {
        l = _l;
        r = _r;
        add = _a;
    }
};

inline void solve() {
    int n; 
    cin >> n;
    map<int, vector<line>> mp;
    int prvX = INF;
    for (int i = 0; i < n; i++) {
        int x[2], y[2];
        cin >> x[0] >> y[0] >> x[1] >> y[1];
        y[1]--;
        mp[x[0]].eb(line(y[0], y[1], 1));
        mp[x[1]].eb(line(y[0], y[1], -1));
        prvX = min(prvX, x[0]);
    }

    int ans = 0;
    for (auto [x, v] : mp) {
        int len = x - prvX;
        ans += len * seg[1];
        for (auto l : v) 
            modify(l.l, l.r, l.add);
        prvX = x;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
