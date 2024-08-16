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

struct Dijkstra {
    static const int mxN = 1e5 + 5;
    vector<pii> g[mxN];
    int dis[mxN], n;
    int cnt[mxN];

    Dijkstra(int _n) : n(_n) {
        fill(dis, dis + n + 1, INF);	
        fill(cnt, cnt + n + 1, 0);	
    }

    void add_edge(int u, int v, int w) {
        g[u].eb(v, w);
        // g[v].eb(u, w);
    }

    int dijkstra(int s, int t) {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        dis[s] = 0; pq.push(0, s);
        cnt[s] = 1;

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            //test(u, cnt[u]);
            if (d > dis[u]) continue;
            for (auto [v, w] : g[u]) {
                if (dis[v] > d + w) {
                    dis[v] = d + w;
                    pq.push(dis[v], v);
                    cnt[v] = cnt[u];
                } else if (dis[v] == d + w) {
                    cnt[v] += cnt[u];
                }
            }
        }
        return dis[t];
    }
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> edge; 
    Dijkstra G(n), rG(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge.push_back({a, b, c});
        G.add_edge(a, b, c);
        rG.add_edge(b, a, c);
    }
    int sp = G.dijkstra(1, 2);
    int totcnt = G.cnt[2];
    rG.dijkstra(2, 1);

    for (auto [a, b, c] : edge) {
        if (G.dis[b] + rG.dis[a] + c < sp) {
            cout << "HAPPY\n";
        } else if (G.dis[a] + c + rG.dis[b] == sp && totcnt == G.cnt[a] * rG.cnt[b]) {
            if (G.dis[b] + rG.dis[a] + c == sp) 
                cout << "SOSO\n";
            else 
                cout << "SAD\n";
        } else {
            cout << "SOSO\n";
        }
    }
}

signed main() {
	IO;	
	solve();	
}
