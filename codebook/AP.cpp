int n, m, k, eu[mxM], ev[mxM], cut[mxN];
bitset<mxM> vis;
vector<int> g[mxN];

int dfn[mxN], low[mxN], aimer;
int ans = 0, vtx = 0;
void dfs(int u, int rt) {
	low[u] = dfn[u] = ++aimer;
	int cnt = 0;
	for (int i : g[u]) {
		int v = eu[i] ^ ev[i] ^ u;
		if (vis[i]) continue;
		vis[i] = 1;
		if (!dfn[v]) { 
			dfs(v, rt);
			cnt++;
			low[u] = min(low[u], low[v]);
			if (u != rt and low[v] >= dfn[u]) cut[u] = 1;
		}
		low[u] = min(low[u], dfn[v]);
	}
	if (u == rt and cnt >= 2) {
		cut[u] = 1;
	}
}

