int n, m, k, eu[mxM], ev[mxM], bridge[mxM];
bitset<mxM> vis;
vector<int> g[mxN];

int dfn[mxN], low[mxN], aimer;
int ans = 0;
void dfs(int u, int rt) {
	low[u] = dfn[u] = ++aimer;
	for (int i : g[u]) {
		int v = eu[i] ^ ev[i] ^ u;
		if (vis[i]) continue;
		vis[i] = 1;
		if (!dfn[v]) { 
			dfs(v, rt);
            if (low[v] > dfn[u]) bridge[i] = 1;
			low[u] = min(low[u], low[v]);
		}
		low[u] = min(low[u], dfn[v]);
	}
}
