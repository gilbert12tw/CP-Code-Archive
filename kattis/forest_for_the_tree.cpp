#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define x first
#define y second
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
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

pii add(pii a, pii v, int dir) {
    if (dir == 0) {
        return mkp(a.x + v.x, a.y + v.y);
    } else if (dir == 1) {
        return mkp(a.x + v.y, a.y - v.x);
    } else if (dir == 2) {
        return mkp(a.x - v.x, a.y - v.y);
    } else if (dir == 3) {
        return mkp(a.x - v.y, a.y + v.x);
    } else if (dir == 4) {
        return mkp(a.x + v.x, a.y - v.y);
    } else if (dir == 5) {
        return mkp(a.x - v.x, a.y + v.y);
    } else if (dir == 6) {
        return mkp(a.x + v.y, a.y + v.x);
    } else if (dir == 7) {
        return mkp(a.x - v.y, a.y - v.x);
    }
    return mkp(-1, -1);
}

inline void solve() {
    int n, m, r;
    cin >> n >> m >> r;
    vector<pii> pt(n), s(m);
    map<pii, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> pt[i].x >> pt[i].y;
        mp[pt[i]] = 1;
    }
    for (int i = 0; i < m; i++) 
        cin >> s[i].x >> s[i].y;

    set<pii> ans;
    auto check = [&](pii ori, int dir) {
        for (int i = 0; i < m; i++) {
            pii nxt = add(ori, s[i], dir);
            if (mp[nxt] == 0) return 0;
        }
        return 1;
    };
    for (int dir = 0; dir < 8; dir++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pii nv = mkp(-s[j].x, -s[j].y);
                pii robot = add(pt[i], nv, dir);
                if (check(robot, dir)) {
                    ans.insert(robot);
                }
            }
        }
    }
    if (SZ(ans) > 1) cout << "Ambiguous\n";
    else if (SZ(ans) == 0) cout << "Impossible\n";
    else cout << ans.begin()->x << ' ' << ans.begin()->y << '\n';
}

signed main() {
	IO;	
	solve();	
}
