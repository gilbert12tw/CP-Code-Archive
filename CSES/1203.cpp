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

const int mxN = 1e5 + 5, mxM = 2e5 + 5;

int n, m;
vector<int> gp[mxN];

struct Dijkstra {
    vector<pii> g[mxN];
    int dis[mxN];

    int dijkstra(int s, int t) {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        fill(dis, dis + n + 1, INF);	
        dis[s] = 0;
        pq.push(0, s);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dis[u]) continue;
            for (auto [v, w] : g[u]) {
                if (dis[v] > d + w) {
                    dis[v] = d + w;
                    pq.push(dis[v], v);
                } 
            }
        }
        return dis[t];
    }
} G, GP;

int eu[mxM], ev[mxM], cut[mxN];
bitset<mxM> vis;

int dfn[mxN], low[mxN], df;
vector<int> ans;

void build(int mn) {
    int idx = 0;
    for (int i = 1; i <= n; i++) {
        for (auto [v, w] : G.g[i]) {
            if (G.dis[i] + GP.dis[v] + w == mn) {
                eu[idx] = i;
                ev[idx] = v;
                gp[i].eb(idx);
                gp[v].eb(idx);
                idx++;
            }
        }
    }
}

void tarjan(int u, int e = -1){
	dfn[u] = low[u] = ++df;
    int go_cnt = 0, isAP = 0;
	for(int i : gp[u]){
		int v = eu[i] ^ ev[i] ^ u;
        if (vis[i]) continue;
        vis[i] = 1;
		if (i == e) continue;
        go_cnt++;
		if(!dfn[v]){
			tarjan(v, i);
			low[u] = min(low[u], low[v]);
		} else {
			low[u] = min(low[u], dfn[v]);
		}
        if (low[v] >= dfn[u]) isAP = 1;
	}
 
    if ((e != -1 && isAP) || (e == -1 && go_cnt > 1)) {
        ans.eb(u);
    }
}

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G.g[a].eb(b, c);
        GP.g[b].eb(a, c);
    }
    G.dijkstra(1, n);
    int mn = GP.dijkstra(n , 1);
    build(mn);
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, -1);
    ans.eb(1);
    ans.eb(n);
    sort(ALL(ans));
    uni(ans);
    cout << SZ(ans) << '\n';
    for (int i : ans) cout << i << ' ';
}

signed main() {
	IO;	
	solve();	
}
