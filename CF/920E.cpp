#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
#define inf 1e9
#define INF 1e18
#define mod 1000000007
#define F first
#define S second
#define wopen(x) freopen((x),"w",stdout)
#define ropen(x) freopen((x),"r",stdin)
#define de(x) cout << #x << " = " << x << ' '
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;
void trace_() {cerr << "\n";}
template<typename T1, typename... T2> void trace_(T1 t1, T2... t2) {cerr << ' ' << t1; trace_(t2...); }
#define trace(...) cerr << "[" << #__VA_ARGS__ << "] :", trace_(__VA_ARGS__);

const int mxN = 2e5 + 5;
int n, m, nxt[mxN], prv[mxN];
vector<int> g[mxN];
bitset<mxN> tag;

inline void del(int x) {
    prv[nxt[x]] = prv[x];
    nxt[prv[x]] = nxt[x];
}

signed main() {
    IO;
    cin >> n >> m;
    nxt[0] = 1;
    prv[n + 1] = n;
    for (int i = 1; i <= n; i++) {
        nxt[i] = i + 1;
        prv[i] = i - 1;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].eb(b); g[b].eb(a);
    }
    vector<int> ans;
    while (nxt[0] != n + 1) {
        queue<int> q;
        q.push(nxt[0]);
        int cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cnt++;
            for (int v : g[u]) tag[v] = 1;
            for (int i = nxt[0]; i != n + 1; i = nxt[i]) {
                if (!tag[i]) { 
                    del(i);
                    if (i != nxt[0]) q.push(i);
                }
                else tag[i] = 0;
            }
        }
        ans.eb(cnt);
    }
    cout << sz(ans) << '\n';
    sort(all(ans));
    for (int i : ans) cout << i-1 << ' ';
}

