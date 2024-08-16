#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SZ(a) ((int)a.size())
#define IO ios_base::sync_with_stdio(0); cin.tie(0);

struct DSU {
	vector<int> dsu, sz;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
	int oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return 0; 
		if(sz[a] > sz[b]) swap(a, b);
		dsu[a] = b;
		sz[b] += sz[a];
        return 1;
	}
};

struct Edge {
    int u, v, w;
    Edge (int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
};

long long Boruvka(const int &n, vector<Edge> &edge) {
    DSU dsu(n);
    int cc = n; // # of conected componets
    long long ans = 0;
    while (cc > 1) {
        int ok = 0;
        vector<int> min_edge_index(n + 1, -1);
        for (int i = 0; i < SZ(edge); i++) {
            int u = dsu.get(edge[i].u), v = dsu.get(edge[i].v), w = edge[i].w;
            if (u == v) continue;
            if (min_edge_index[u] == -1 || edge[min_edge_index[u]].w > w) {
                min_edge_index[u] = i;
            }
            if (min_edge_index[v] == -1 || edge[min_edge_index[v]].w > w) {
                min_edge_index[v] = i;
            }
        }
        for (int i = 1; i <= n; i++) {
            int idx = min_edge_index[i];
            if (idx != -1 && dsu.get(i) == i && dsu.oni(edge[idx].u, edge[idx].v)) {
                ok = 1;
                cc--;
                ans += edge[idx].w;
            }
        }
        if (!ok) return -1; // graph is not connected
    }
    return ans;
}

signed main() {
	IO;	
    int n, m;
    cin >> n >> m;
    vector<Edge> edge;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge.emplace_back(Edge(u, v, w));
    }
    long long ans = Boruvka(n, edge);
    if (ans == -1) cout << "IMPOSSIBLE\n";
    else cout << ans << '\n';
}
