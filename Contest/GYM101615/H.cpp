#include<bits/stdc++.h>
//#define loli
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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 2e5 + 5;
struct LC_tree {
    struct Line {
        pii line;
        int ls = 0, rs = 0;
        Line() {
            line = mkp(0, INF);
        }
    } seg[mxN * 15];
    inline int cal(pii l, int x) {
        return l.first * x + l.second;
    }
    int tot = 0;

    void insert(pii t, int &id, int l = 0, int r = 1000000) {
        if (id == 0) id = ++tot;
        test(seg[id].line.first, seg[id].line.second, l, r);
        int mid = (l+r) >> 1;
        if (cal(t, mid) < cal(seg[id].line, mid)) swap(t, seg[id].line);
        if (l == r)  return;
        if (cal(t, l) < cal(seg[id].line, l)) insert(t, seg[id].ls, l, mid);
        if (cal(t, r) < cal(seg[id].line, r)) insert(t, seg[id].rs, mid+1, r);
    }

    int query(int p, int id, int l = 0, int r = 1000000) {
        if (id == 0) return INF;
        if (l == r) return cal(seg[id].line, p);
        int mid = (l+r)>>1;
        if (p <= mid) return min(query(p, seg[id].ls, l, mid), cal(seg[id].line, p));
        return min(query(p, seg[id].rs, mid+1, r), cal(seg[id].line, p));
    }
} LCT;

int root[mxN];

int u[mxN], v[mxN], s[mxN], e[mxN], w[mxN];

inline void solve() {
    int n, m;
    cin >> n >> m;
    map<int, vector<int>> mp;
    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i] >> s[i] >> e[i];
        mp[s[i]].eb(i);
        mp[e[i]].eb(-i);
    }

    int ans = INF;
    LCT.insert(mkp(0, 0), root[1]);

    for (auto [tm, vec] : mp) {
        for (int i : vec) {
            if (i > 0) {
                if (root[u[i]] == 0) { 
                    w[i] = INF;
                    continue;
                }
                test(u[i], tm, LCT.query(root[u[i]], tm));
                w[i] = LCT.query(tm, root[u[i]]) + tm * tm;
            }
        }
        for (int i : vec) {
            if (i < 0) {
                if (w[-i] != INF) {
                    test(w[-i], v[-i]);
                    LCT.insert(mkp(-2 * tm, tm * tm + w[-i]), root[v[-i]]);
                    if (v[-i] == n) 
                        ans = min(ans, w[-i]);
                }
            }
        }
    }
    assert(root[n] != 0);
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
