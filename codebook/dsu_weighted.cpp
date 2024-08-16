struct DSU {
	vector<int> dsu, w;
	DSU() {}
	DSU(int n) {
		dsu.resize(n + 1);
		w.resize(n + 1, 0);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	pii get(int x) {
		if (dsu[x] == x) return mkp(x, 0);
		pii pa = get(dsu[x]);
		w[x] ^= w[dsu[x]];
		return mkp(dsu[x] = pa.X, w[x]);
	}
	void oni(int x, int y, int v) {
		pii a = get(x), b = get(y);
		if(a.X == b.X) return; 
		dsu[a.X] = b.X;
		w[a.X] = v ^ a.Y ^ b.Y;
	}
};
