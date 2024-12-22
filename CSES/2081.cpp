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

const int mxN = 2e5 + 5;
int n, k1, k2;

// persistent segment tree
struct persistent_segment {
	int ls[mxN * 40], rs[mxN * 40], seg[mxN * 40], tot, etot;
	#define mid ((l+r)>>1)

	inline void up(int id) {
		seg[id] = seg[ls[id]] + seg[rs[id]];
	}

	inline void copy(int id, int p) {
		ls[id] = ls[p]; rs[id] = rs[p]; seg[id] = seg[p];
	}

    int merge(int a, int b, int l = 0, int r = n) {
        if (a == 0 || b == 0) return a | b;
        int id = ++tot;
        seg[id] = seg[a] + seg[b];
        ls[id] = merge(ls[a], ls[b], l, mid);
        rs[id] = merge(rs[a], rs[b], mid+1, r);
        return id;
    }

	void modify(int &id, int pos, int v, int l = 0, int r = n) {
		int p = id;
		id = ++tot;
		if (l == r) {
			seg[id] = v;
			return;
		}
		copy(id, p); 
		if (pos <= mid) modify(ls[id], pos, v, l, mid);
		else modify(rs[id], pos, v, mid + 1, r);
		up(id);
	}

	int query(int ed, int a, int b, int l = 0, int r = n) {
        if (a > n) return 0;
        if (b > n) b = n;
        if (l > r) return 0;
		if (a <= l and r <= b) return seg[ed];
		int res = 0;
		if (a <= mid) res = query(ls[ed], a, b, l, mid);
		if (b > mid) res += query(rs[ed], a, b, mid+1, r);
		return res;
	}
} seg;

vector<int> G[mxN], dp[mxN];
int dep[mxN], mx[mxN], edit[mxN], bson[mxN];

void get_dep(int u, int p) {
    bson[u] = -1;
    for (int v : G[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        get_dep(v, u);
        mx[u] = max(mx[u], mx[v] + 1);
        if (bson[u] == -1 || mx[v] > mx[bson[u]]) bson[u] = v;
    }
}

int ans = 0;
void dfs(int u, int p) {
    if (bson[u] != -1) {
        dfs(bson[u], u);
        //swap(dp[u], dp[bson[u]]);
        dp[u] = move(dp[bson[u]]);
        ans += seg.query(edit[bson[u]], dep[u] + k1, dep[u] + k2);
        edit[u] = edit[bson[u]];
    }
    
    for (int v : G[u]) {
        if (v == p || v == bson[u]) continue;
        dfs(v, u);

        // merge
        ans += seg.query(edit[v], dep[u] + k1, dep[u] + k2);
        int len = 1;
        for (int i = SZ(dp[u]) - 1, j = SZ(dp[v]) - 1; j >= 0; i--, j--, len++) {
            assert(i >= 0);
            dp[u][i] += dp[v][j];
            if (len <= k2) ans += seg.query(edit[u], max(0ll, dep[u] + k1 - len), max(0ll, dep[u] + k2 - len)) * dp[v][j];
        }
        dp[v].clear();
        edit[u] = seg.merge(edit[u], edit[v]);
    }

    dp[u].eb(1);
    seg.modify(edit[u], dep[u], 1);
}

inline void solve() {
    cin >> n >> k1 >> k2;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].eb(v);
        G[v].eb(u);
    }
    get_dep(1, 0);
    dfs(1, 0);
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
