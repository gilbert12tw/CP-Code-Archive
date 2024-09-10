#include<bits/stdc++.h>
#define x first
#define y second
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mem(x,val) memset(x,val,sizeof x)
#define pii pair<int,int>
#define pb emplace_back
#define ar array
#define int long long
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define F0R(i, n) FOR(i, 0, n)
#define FOR1(i, n) FOR(i, 1, n+1)
#define wopen(x) freopen((x),"w",stdout)
#define ropen(x) freopen((x),"r",stdin)
using namespace std;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int n, m, a[100005], b[100005], c[105], ans[100005];
vector<int> g[105];
bitset<105> vis;

void dfs(int u, int p = 0) {
    vis[u] = 1;
    for(int i : g[u]){
        int v = a[i] ^ b[i] ^ u;
        if (v == p) continue;
        if (ans[i] == -1) {
            ans[i] = (v == a[i]);
        }
        if (!vis[v]) dfs(v, u);
    }
}

signed main(void){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    memset(ans, -1, sizeof(ans));
    for(int i = 0; i < m; i++)
        cin >> a[i] >> b[i];
    for(int i = 1; i <= n; i++)
        cin >> c[i];
    for(int i = 0; i < m; i++){
        if(c[a[i]] > c[b[i]]) ans[i] = 0;
        else if(c[a[i]] < c[b[i]]) ans[i] = 1;
        else {
            g[a[i]].pb(i);
            g[b[i]].pb(i);
        }
    }
    for(int i = 1; i <= n; i++){
        if(vis[i]) continue;
        dfs(i);
    }
    for(int i = 0; i < m; i++){
        cout << (ans[i] ? "<-" : "->") << '\n';
    }
}

