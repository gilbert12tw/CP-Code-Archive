struct DSU {
	vector<int> dsu, sz;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1);
		for (int i = 1; i <= n; i++) {
            dsu[i] = i;
            sz[i] = 1;
        }
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
    int get_sz(int x) {
        return sz[get(x)];
    }
	void oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return; 
		dsu[a] = b;
		sz[b] += sz[a];
	}
};


struct FindBrindge {
    int bridges;
    DSU dsu, bcc;
    vector<int> pa;
    vector<int> dep;
    vector<int> tp;
    vector<vector<int>> tr;
    FindBrindge(int n): bridges(0), dsu(n), bcc(n), pa(n + 1), dep(n + 1), tp(n + 1), tr(n + 1) {
        for (int i = 1; i <= n; i++) tp[i] = i;
    }

    void reroot(int u, int p) {
        //if (pa[u] == p) return;
        pa[u] = p;
        dep[u] = dep[p] + 1;
        for (int v : tr[u]) {
            if (v == p) continue;
            reroot(v, u);
        }
    }

    void checkroot(int u, int p) {
        //if (pa[u] == p) return;
        int x = tp[bcc.get(u)];
        if (dep[x] > dep[u]) {
            tp[x] = u;
        }
        for (int v : tr[u]) {
            if (v == p) continue;
            checkroot(v, u);
        }
    }

    void merge(int u, int v) {
        u = tp[bcc.get(u)];
        v = tp[bcc.get(v)];
        while (u != v) {
            if (dep[u] < dep[v])
                swap(u, v);
            bcc.oni(u, pa[u]);
            u = tp[bcc.get(u)];
            bridges--;
        }
    }

    void add_edge(int u, int v) {
        if (dsu.get(u) == dsu.get(v)) {
            merge(u, v);
            return;
        }
        if (dsu.get_sz(u) > dsu.get_sz(v)) 
            swap(u, v);
        dsu.oni(u, v);
        reroot(u, v);
        checkroot(u, v);
        tr[u].eb(v); tr[v].eb(u);
        bridges++;
    }

    int get_bridges() { return bridges; }
};

