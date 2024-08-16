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
 
int n, a[51], b[51];
 
struct Dinic {
    struct edge {
        int u, v, cap, flow;
        edge(int u, int v, int cap): u(u), v(v), cap(cap), flow(0) {}
    };
    vector<edge> edges;
    vector<vector<int>> adj;
    vector<int> level, num;
    queue<int> q;
    int n, s, t, cnt = 0; //To maintain the id of edges
 
    void init(int nn, int ss, int tt) {
        n = nn + 1, s = ss, t = tt;
        adj.resize(n);
        level.resize(n);
        num.resize(n);
    }
 
    void add_edge(int u, int v, int cap) {
    	//cout << u << " " << v << " " << cap << "\n";
        edges.push_back({u, v, cap});
        edges.push_back({v, u, 0});
        adj[u].push_back(cnt++);
        adj[v].push_back(cnt++);
    }
 
    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
 
        while (!q.empty()) {
            int u = q.front();
            q.pop();
 
            for (auto eid : adj[u]) {
                edge e = edges[eid];
 
                //We only pass the edge that has positive capacity
                if (e.cap - e.flow <= 0 || level[e.v] != -1)
                    continue;
 
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
        //If we cannot reach t, then there is no Augmenting Path
        return level[t] != -1;
    }
 
    int dfs(int u, int now) {
        if (now == 0)
            return 0;
        if (u == t)
            return now;
 
        for (; num[u] < adj[u].size(); num[u]++) {
            edge e = edges[adj[u][num[u]]];
 
            if (level[e.v] != level[u] + 1 || e.cap - e.flow <= 0)
                continue;
 
            int f = dfs(e.v, min(now, e.cap - e.flow));
 
            if (!f)
                continue;
 
            edges[adj[u][num[u]]].flow += f;
            edges[adj[u][num[u]] ^ 1].flow -= f;
            return f;
        }
        return 0;
    }
 
    int get_flow() {
        int res = 0, now;
 
        while (true) {
            if (!bfs())
                break;
 
            fill(num.begin(), num.end(), 0);
 
            while (now = dfs(s, INF)) {
                res += now;
            }
        }
        return res;
    }
} flow;
 
char mat[51][51];
 
inline void solve() {
    cin >> n;
    flow.init(2 * n + 1, 0, 2 * n + 1);
    int suma = 0, sumb = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        flow.add_edge(0, i, a[i]);
        suma += a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        flow.add_edge(i+n, 2 * n + 1, b[i]);
        sumb += b[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            flow.add_edge(i, j + n, 1);
        }
    }
 
    if (suma != sumb) {
        cout << -1 << '\n';
        return;
    }
 
    if (flow.get_flow() != suma) {
        cout << -1 << '\n';
        return;
    }
 
    for (int i = 1; i <= n; i++) {
        for (int id : flow.adj[i]) {
            if (flow.edges[id].v == 0) continue;
            if (flow.edges[id].flow == 1) {
                mat[i][flow.edges[id].v - n] = 'X'; 
            } else {
                mat[i][flow.edges[id].v - n] = '.';
            }
        }
    }
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << mat[i][j];;
        cout << '\n';
    }
}
 
 
signed main() {
	IO;	
	solve();	
}
