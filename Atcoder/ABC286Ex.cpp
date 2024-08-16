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

const int mxN = 2e6 + 5;

#define x first
#define y second
#define point pii

point operator + (point a, point b) {
	return point(a.x + b.x, a.y + b.y);	
}
point operator - (point a, point b) {
	return point(a.x - b.x, a.y - b.y);	
}
inline int dis2(point a, point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline int cross(point a, point b) {
	return a.x * b.y - a.y * b.x;
}
inline int dot(point a, point b) {
	return a.x * b.x + a.y * b.y;
}


class Point {
private:
    int x, y;
public:
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};


bool cmp(point a, point b) {
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

vector<point> build(vector<point> p) {
	vector<point> up, dn;	
	sort(ALL(p), cmp);
	for(int i = 0; i < SZ(p); i++) {
		while(SZ(up) > 1 and cross(up[SZ(up) - 1] - up[SZ(up) - 2], p[i] - up[SZ(up) - 2]) > 0)
			up.pop_back();
		while(SZ(dn) > 1 and cross(dn[SZ(dn) - 1] - dn[SZ(dn) - 2], p[i] - dn[SZ(dn) - 2]) < 0)
			dn.pop_back();
		dn.pb(p[i]);
		up.pb(p[i]);
	}
	reverse(ALL(dn));
	for (int i = 1; i + 1 < SZ(dn); i++) up.eb(dn[i]);
	return up;
}

inline void solve() {
    int n; cin >> n;
    vector<point> v(n), cvx;
    point s, t;
    for (auto &i : v) cin >> i;
    cin >> s >> t;
    v.eb(s);
    v.eb(t);
    cvx = build(v);
    int stid = -1, endid = -1;
    double sum = 0;
    for (int i = 0; i < SZ(cvx); i++) {
        if (cvx[i] == s) stid = i;
        if (cvx[i] == t) endid = i;
        sum += sqrt(dis2(cvx[i], cvx[(i + 1) % SZ(cvx)]));
    }

    double ans = sqrt(dis2(s, t));
    double mn = 0;
    if (stid != -1 && endid != -1) {
        while (stid != endid) {
            mn += sqrt(dis2(cvx[stid], cvx[(stid + 1) % SZ(cvx)]));
            stid = (stid+1) % SZ(cvx);
        }
        ans = min(mn, sum - mn);
    } 

    cout << fixed << setprecision(10) << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
