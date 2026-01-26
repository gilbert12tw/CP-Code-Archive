#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define x first
#define y second
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

#define point pair<ll, ll>
#define x first
#define y second
ll cross(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}

inline int get_region(const point &p) {
    if (p.x > 0 || (p.x == 0 && p.y > 0)) return 0;
    return 1;
}

bool cmp(const point &a, const point &b) {
    int ra = get_region(a), rb = get_region(b);
    if (ra != rb) return ra < rb;
    return cross(a, b) < 0; // counter-clockwise
}

inline void solve() {
    int n, q;
    cin >> n >> q;
    vector<point> pt;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pt.eb(x, y);
    }
    vector<int> ord(n);
    iota(ALL(ord), 0);
    sort(ALL(ord), [&](int a, int b) {
        return cmp(pt[a], pt[b]);
    });
    
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        int rr = i;
        while (rr + 1 < n && cmp(pt[ord[i]], pt[ord[rr + 1]]) == false) {
            rr++;
        }
        for (int j = i; j <= rr; j++) {
            l[j] = i;
            r[j] = rr;
        }
        i = rr;
    }

    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[ord[i]] = i;
        test(pt[ord[i]].x, pt[ord[i]].y);
        test(l[i], r[i]);
        test(ord[i]);
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        int pa = pos[a], pb = pos[b];
        if (l[pa] == l[pb] && r[pa] == r[pb]) {
            cout << r[pb] - l[pb] + 1 << '\n';
            continue;
        }
        if (pa < pb) {
            cout << r[pb] - l[pa] + 1 << '\n';
        } else {
            cout << (n - l[pa] + r[pb] + 1) << '\n';
        }
    }
}

signed main() {
	IO;	
	solve();	
}
