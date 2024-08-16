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

const int mxN = 500 + 5;

struct MCMF {
	static const int mxE = 1e5 + 5, mxN = 505;

	int eu[mxE], ev[mxE], w[mxE], cap[mxE], dir[mxE], tot;
	vector<int> g[mxN];

	inline void addEdge(int x, int y, int ew, int c) {
		g[x].eb(tot);
		eu[tot] = x; ev[tot] = y; w[tot] = ew; dir[tot] = 1; cap[tot++] = c;
		g[y].eb(tot);
		ev[tot] = x; eu[tot] = y; w[tot] = -ew; dir[tot] = 0; cap[tot++] = 0;
	}

    // longest path by SPFA
	inline int SPFA(int s, int t, int &ans, int &mxflow) {
		vector<int> dis(mxN, -INF), from(mxN, 0), in(mxN, 0), lim(mxN, 0);
		dis[s] = 0;
        lim[s] = INF;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			in[u] = 0;
			for (int i : g[u]) {
				int v = ev[i];
				if (cap[i] > 0 && dis[v] < dis[u] + w[i]) {
					dis[v] = dis[u] + w[i];
                    lim[v] = min(lim[u], cap[i]); 
					from[v] = i;
					if (!in[v]) q.push(v);
					in[v] = 1;
				}
			}
		}
		if (dis[t] <= -INF) return 0;
        int flcnt = lim[t];
        ans -= dis[t] * flcnt;
        mxflow += flcnt;
 
		while (t != s) {
			int e = from[t];	
            cap[e] -= flcnt;
            cap[e^1] += flcnt; 
			t = eu[e];
		}
		return 1;
	}

	pii run(int s, int t) {
        int ans = 0, fl = 0;
		while (SPFA(s, t, ans, fl));
        return mkp(ans, fl);
	}
} flow;

int n, m, k;

void bfs() {
    queue<int> q;
    vector<int> from(n + 1, 0);

    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == n) {
            int t = n;
            vector<int> ans;
            while (t != 1) {
                flow.cap[from[t]] = 1;
                ans.eb(t);
                t = flow.eu[from[t]] ^ flow.ev[from[t]] ^ t; 
            }
            ans.eb(1);
            reverse(ALL(ans));
            cout << SZ(ans) << '\n';
            for (int i : ans) cout << i << ' ';
            cout << '\n';

            return;
        }

        for (int e : flow.g[u]) {
            int v = u ^ flow.eu[e] ^ flow.ev[e];
            if (flow.dir[e] == 0 || v == 0 || from[v] || flow.cap[e] != 0) 
                continue;

            q.push(v);
            from[v] = e;
        }
    }
}

if ((j_max > 0 && D[A[j_max] - 1] < 0 && A[j_max-1] < A[j_max]) || 
    (j_max < (N-1) && D[A[j_max] - 1] > 0 && A[j_max] > A[j_max + 1]))


inline void solve() {
    cin >> n >> m >> k;

    flow.addEdge(0, 1, 0, k);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        flow.addEdge(u, v, -1, 1);
    }
    pii ans = flow.run(0, n);

    if (ans.S != k) {
        cout << -1 << '\n';
    } else {
        cout << ans.F << '\n';
        while (ans.S--) { 
            bfs();
        }
    }

}

signed main() {
	IO;	
	solve();	
}
