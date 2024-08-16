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
const int mxL = 20;
struct linear_base {
    int len;
    vector<int> bas, tm;

    linear_base(): bas(mxL, 0), tm(mxL, -1), len(0) {}

	void insert(int x, int t) {
		for (int i = mxL; i >= 0; i--) {
			if (get_bit(x, i)) {
				if (bas[i]) { 
                    if (tm[i] < t) {
                        swap(tm[i], t);
                        swap(bas[i], x);
                    }
                    x ^= bas[i];
                } else {
					bas[i] = x;
                    tm[i] = t;
					len++;
					break;
				}
			}
		}
	}

    int check(int x) {
        int mn = inf;
        for (int i = mxL; i >= 0; i--) {
            if (get_bit(x, i)) {
                if (bas[i] == 0) return -1;
                x ^= bas[i];
                mn = min(mn, tm[i]);
            }
        }
        return mn;
    }
} bases[mxN];

// LCA binary jump
vector<int> g[mxN];
int a[mxN];
int up[mxN][25], dep[mxN];
const int mxD = 20;

void dfs(int u, int p = -1) {
	if (p != -1) {
        up[u][0] = p;
        bases[u] = bases[p];
    }

    bases[u].insert(a[u], dep[u]);

	for (int i = 1; (1<<i) <= dep[u]; i++) {
		up[u][i] = up[up[u][i-1]][i-1];
	}

	for (int v : g[u]) {
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

inline int lca(int u, int v) {
	if (u == v) return u;
	if (dep[u] < dep[v]) swap(u, v);

	for (int i = mxD; i >= 0; i--) {
		if (up[u][i] and dep[up[u][i]] >= dep[v]) {
			u = up[u][i];
		}
	}

	if (u == v) return u;

	for (int i = mxD; i >= 0; i--) {
		if (up[u][i] and up[v][i] and up[u][i] != up[v][i]) {
			u = up[u][i];
			v = up[v][i];
		}
	}

	return up[u][0];
}


inline void solve() {
    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        g[x].eb(y);
        g[y].eb(x);
    }

    dfs(1);

    cin >> q;
    while (q--) {
        int x, y, k;
        cin >> x >> y >> k;
        int d = dep[lca(x, y)];
        //test(d);
        // merge
        linear_base res = bases[x];
        for (int i = mxL; i >= 0; i--) {
            if (bases[y].bas[i]) 
                res.insert(bases[y].bas[i], bases[y].tm[i]);
        }
        if (res.check(k) >= d) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

signed main() {
	IO;	
	solve();	
}
