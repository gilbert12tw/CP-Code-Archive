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

const int mxM = 305, mxN = 105;
int ec[mxM], et[mxM], eu[mxM], ev[mxM];
vector<int> g[mxN];

inline void solve() {
    int n, m, s, e;
    cin >> n >> m >> s >> e;

    int sumc = 0;
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i] >> ec[i] >> et[i];
        g[eu[i]].eb(i);
        g[ev[i]].eb(i);
        sumc += ec[i];
    }

    test(sumc);
    vector<vector<int>> dis(n + 1, vector<int>(sumc + 1, inf));

#define piii pair<int, pii>
    priority_queue<piii, vector<piii>, greater<piii>> pq;
    dis[s][0] = 0;
    pq.push(0, mkp(s, 0));
    while (!pq.empty()) {
        auto [wc, uid] = pq.top(); pq.pop();
        int u = uid.first, sc = uid.second;
        if (wc > dis[u][sc]) continue;
        for (int eid : g[u]) {
            int c = ec[eid];
            int t = et[eid];
            int v = u ^ eu[eid] ^ ev[eid];
            if (dis[v][sc + c] > dis[u][sc] + t) {
                dis[v][sc + c] = dis[u][sc] + t;
                pq.push(dis[u][sc] + t, mkp(v, sc + c));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= sumc; i++) if (dis[e][i] < inf) {
        test(dis[e][i]);
        ans++;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
