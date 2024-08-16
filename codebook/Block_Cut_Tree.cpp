//Block Cut Tree
const int mxM = 1e6, mxN = 1e6; // N double size
int n, m, k, eu[mxM], ev[mxM];
bitset<mxM> vis;
vector<int> g[mxN], tr[mxN];

int dfn[mxN], low[mxN], aimer, bcnt;
vector<int> stk;

void Tarjan(int u, int rt) {
	low[u] = dfn[u] = ++aimer;
    stk.eb(u);
	for (int i : g[u]) {
		int v = eu[i] ^ ev[i] ^ u;
		if (vis[i]) continue;
		vis[i] = 1;
		if (!dfn[v]) { 
			Tarjan(v, rt);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) { 
                ++bcnt; 
                int x = stk.back();
                do {
                    x = stk.back(); stk.pop_back();
                    tr[bcnt + n].eb(x);
                    tr[x].eb(bcnt + n);
                } while (x != v);
                // add a node bcnt + n
                tr[bcnt + n].eb(u);
                tr[u].eb(bcnt + n);
            }
		}
		low[u] = min(low[u], dfn[v]);
	}
}

void build_BCT() {
    for (int i = 1; i <= n; i++) if (!dfn[i]) {
        stk.clear();
        Tarjan(i, i);
    }
}
