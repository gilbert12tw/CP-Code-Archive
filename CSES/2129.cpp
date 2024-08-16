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

const int mxN = 201;

int n, c[mxN][mxN];

// shortest path max flow
struct MCMF {
	static const int mxE = 1e5 + 5, mxN = 405;
	int eu[mxE], ev[mxE], w[mxE], cap[mxE], tot;
	vector<int> g[mxN];
	inline void addEdge(int x, int y, int ew, int c) {
		g[x].eb(tot);
		eu[tot] = x; ev[tot] = y; w[tot] = ew; cap[tot++] = c;
		g[y].eb(tot);
		ev[tot] = x; eu[tot] = y; w[tot] = -ew; cap[tot++] = 0;
	}
	inline int SPFA(int s, int t, int &ans) {
		vector<int> dis(mxN, INF), from(mxN, 0), in(mxN, 0);
		dis[s] = 0;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			in[u] = 0;
			for (int i : g[u]) {
				int v = ev[i];
				if (cap[i] > 0 && dis[v] > dis[u] + w[i]) {
					dis[v] = dis[u] + w[i];
					from[v] = i;
					if (!in[v]) q.push(v);
					in[v] = 1;
				}
			}
		}
		if (dis[t] >= INF) return 0;
        ans += dis[t];
		while (t != s) {
			int e = from[t];	
			swap(cap[e], cap[e^1]);
			t = eu[e];
		}
		return 1;
	}
	int run(int s, int t) {
        int ans = 0;
		while (SPFA(s, t, ans));
        return ans;
	}
} flow;




inline void solve() {
    cin >> n;
    /*  
     * task in -> task out
     * [i -> tin_j] (c[i][j], 1)
     * [tin -> end] (0, 1);
     * s = 0
     * t = 2 * n + 1
     */
    for (int i = 1; i <= n; i++) {
        flow.addEdge(0, i, 0, 1);
        for (int j = 1; j <= n; j++) {
            cin >> c[i][j];
            flow.addEdge(i, j + n, c[i][j], 1);
        }
        flow.addEdge(i + n, 2 * n + 1, 0, 1);
    }

    cout << flow.run(0, 2 * n + 1) << '\n';
    for (int i = 1; i <= n; i++) {
        for (int id : flow.g[i]) {
            int v = flow.eu[id] ^ flow.ev[id] ^ i;
            if (flow.cap[id] == 0) {
                cout << i << ' ' << v - n << '\n';
                break;
            }
        }
    }
}

signed main() {
	IO;	
	solve();	
}
