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
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

int q, k;
set<int> pt;
struct node {
	int l, r, v;
	node(int il, int ir, int iv) : l(il), r(ir), v(iv) {}
	bool operator < (const node a) const {
		return l < a.l;
	}
    node operator + (const node a) const {
        node t = a;
        t.l = min(t.l, l);
        t.r = max(t.r, r);
        t.v += v;
        return v;
    }
};
set<node> odt;

void insert(int x) {
    auto it = pt.insert(x).first; 
    auto nd = odt.insert(node(x, x, 1)).first;
    if (*it - *prev(it) <= k) {
        auto nxt = *nd + *prev(nd); 
        odt.erase(prev(nd));
        odt.erase(nd);
        nd = odt.insert(nxt).first;
    }
    if (*next(it) - *it <= k) {
        auto nxt = *nd + *next(nd); 
        odt.erase(next(nd));
        odt.erase(nd);
        nd = odt.insert(nxt).first;
    }
}

void erase(int x) {
    auto it = pt.find(x);
    int pv = *prev(it), nx = *next(it);
    if (x - pv <= k && nx - x <= k) {
        if (nx - pv <= k) {
            auto nd = qry(x);
            odt.erase(nd);
            nd.v -= 1;
            odt.inesrt(nd);
        } else {
            auto nd = qry(x);
            odt.erase(nd);
        }
        auto nxt = *nd + *prev(nd); 
        odt.erase(prev(nd));
        odt.erase(nd);
        nd = odt.insert(nxt).first;

    }
    if (*next(it) - *it <= k) {
        auto nxt = *nd + *next(nd); 
        odt.erase(next(nd));
        odt.erase(nd);
        nd = odt.insert(nxt).first;
    }
    pt.erase(x);
}

node qry(int x) {
    auto it = prev(odt.upper_bound(node(x, INF, INF))).first;
    return *it;
}

inline void solve() {
    cin >> q >> k;

    pt.insert(-INF);
    pt.insert(INF);
    odt.insert(node(-INF, -INF, 0));
    odt.insert(node(INF, INF, 0));

    while (q--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) {

        } else {
        }
        }
    }
}

signed main() {
	IO;	
	solve();	
}
