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


struct DSU {
	vector<int> dsu, sz, pw;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
        pw.resize(n + 1, -inf);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
        while (x != dsu[x]) x = dsu[x];
        return x;
	}
	void oni(int a, int b, int w) {
		a = get(a), b = get(b);
		if(a == b) return; 
		if(sz[a] > sz[b]) swap(a, b);
		dsu[a] = b;
        pw[a] = w;
		sz[b] += sz[a];
	}
    int query(int a, int b) {
        int res = inf;
        while (a != b) {
            test(a, b);
            if (pw[a] > pw[b]) {
                res = pw[a];
                a = dsu[a];
            } else {
                res = pw[b];
                b = dsu[b];
            }
        }
        return res;
    }
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, pii>> buildings;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int f; cin >> f;
            buildings.eb(mkp(f, mkp(i, j)));
        }
    }

    auto hsh = [&](pii p) -> int {
        return p.x * m + p.y;
    };

    sort(ALL(buildings)); reverse(ALL(buildings));

    vector<vector<int>> vis(n, vector<int>(m));
    DSU dsu(n * m);
    {
        const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
        for (auto [val, pos] : buildings) {
            for (int d = 0; d < 4; d++) {
                int x = pos.x + dx[d], y = pos.y + dy[d];
                if (x >= 0 && x < n && y >= 0 && y < m && vis[x][y]) {
                    dsu.oni(hsh(pos), hsh(mkp(x, y)), val);
                }
            }
            vis[pos.x][pos.y] = 1;
        }
    }

    int q; cin >> q;
    while (q--) {
        int a, b, y, c, d, f;
        cin >> a >> b >> y >> c >> d >> f;
        a--; b--; c--; d--;
        int mn = dsu.query(hsh(mkp(a, b)), hsh(mkp(c, d)));
        test(mn);
        if (mn < min(y, f)) cout << abs(y - mn) + abs(f - mn) << '\n';
        else cout << abs(y - f) << '\n';
    }

}

signed main() {
	IO;	
	solve();	
}
