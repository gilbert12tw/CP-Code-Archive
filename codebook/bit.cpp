struct BIT{
    vector<int> b;
    int n;
    BIT(int _n): b(_n + 1), n(_n) {}
    void build(int a[]) {
        for (int i = 1; i <= n; i++) {
            b[i] += a[i];
            int j = i + (i&-i);
            if (j <= n) b[j] += b[i];
        }
    }
	int qry(int i) {
		int res = 0;
		for (; i > 0; i -= (i&-i)) res += b[i];
		return res;
	}
	void upd(int i, int v) {
		for (; i <= n; i += (i&-i)) b[i] += v; 
	}
	int findk(int k) {
		int id = 0, res = 0;
		int mx = __lg(n) + 1;
		for (int i = mx; i >= 0; i--) {
			if ((id | (1<<i)) > n) continue;
			if (res + b[id|(1<<i)] < k) { 
				id = (id | (1<<i));
				res += b[id];
			}
		}
		return id + 1;
	}
};
