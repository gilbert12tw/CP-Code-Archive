int dsu[mxN], lca[mxN], qu[mxN], qv[mxN];
vector<int> g[mxN], q[mxN];
bitset<mxN> used;

int get(int x) {
	return x == dsu[x] ? x : dsu[x] = get(dsu[x]);
}

void tarjan(int u, int p = -1) {
	for(int v : g[u]) if(v != p) tarjan(v, u);
	for(int i : q[u]) {
		int v = u ^ qu[i] ^ qv[i];
		if(used[v]) {
			lca[i] = get(v);
		}
		if (v == u) lca[i] = u;
	}
	used[u] = 1;
	dsu[u] = p;
}

