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

struct MCMF {
    int n;
    vector<int> eu, ev, w, cap;
    vector<vector<int>> g;
    MCMF (int _n): n(_n + 1), g(_n + 1) {}

    inline void addEdge(int x, int y, int ew, int c) {
        g[x].eb(SZ(eu));
        eu.eb(x); ev.eb(y); w.eb(ew); cap.eb(c);
        g[y].eb(SZ(eu));
        ev.eb(x); eu.eb(y); w.eb(-ew); cap.eb(0);
    }
    // longest path by SPFA
    inline int SPFA(int s, int t, int &ans, int &mxflow) {
        vector<int> dis(n, -INF), from(n, 0), in(n, 0), lim(n, 0);
        dis[s] = 0; lim[s] = INF;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            in[u] = 0;
            for (int i : g[u]) {
                int v = ev[i]; // change this 
                //test(v, cap[i], dis[v], dis[u], w[i]);
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
        int flcnt = lim[t]; // or ans += dis[t]
        ans += dis[t] * flcnt;
        mxflow += flcnt;
        //test(dis[t]);
        while (t != s) {
            int e = from[t];	
            cap[e] -= flcnt; cap[e^1] += flcnt; 
            t = eu[e];
        }
        return 1;
    }
    pii run(int s, int t) {
        int ans = 0, fl = 0;
        while (SPFA(s, t, ans, fl));
        return mkp(ans, fl);
    }
};

inline void solve() {
    int n;
    while (cin >> n && n > 0) {
        MCMF flow(n * n + 2);
        int s = 0, t = n * n + 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int w; cin >> w;
                flow.addEdge(i, j + n, max(0ll, w), 1);
            }
        }
        for (int i = 1; i <= n; i++) flow.addEdge(s, i, 0, 1);
        for (int i = 1; i <= n; i++) flow.addEdge(i + n, t, 0, 1);
        int ans = 0;
        ans = max(ans, flow.run(s, t).first);
        cout << ans << '\n';
    }
}

signed main() {
    IO;	
    solve();	
}
