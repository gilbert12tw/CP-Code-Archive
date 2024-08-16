#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<bitset>
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

struct DSU {
	vector<int> dsu, sz;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
	void oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return; 
		if(sz[a] > sz[b]) swap(a, b);
		dsu[a] = b;
		sz[b] += sz[a];
	}
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dsu.oni(u, v);
    }

    set<pii> st;
    int k; cin >> k;
    int ok = 1;
    while (k--) {
        int u, v;
        cin >> u >> v;
        if (dsu.get(u) == dsu.get(v)) {
            ok = 0;
        } 
        else {
            int mn = min(dsu.get(u), dsu.get(v));
            int mx = max(dsu.get(u), dsu.get(v));
            st.insert(mkp(mn, mx));
        }
    }

    int q; cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;

        if (!ok) cout << "No\n";
        else {
            int mn = min(dsu.get(u), dsu.get(v));
            int mx = max(dsu.get(u), dsu.get(v));
            if (st.find(mkp(mn, mx)) != st.end()) 
                cout << "No\n";
            else 
                cout << "Yes\n";
        }
    }

}

signed main() {
	IO;	
	solve();	
}
