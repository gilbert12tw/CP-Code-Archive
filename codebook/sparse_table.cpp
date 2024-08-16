void build() {
	for(int i = 0; (1<<i) <= n; i++) {
		for(int j = 0; j + (1<<i) - 1 < n; j++) {
			st[j][i + 1] = max(st[j][i], st[j + (1<<i)][i]);
		}
	}
}

int query(int l, int r) {
	int k = __lg(r - l + 1);
	return max(st[l][k], st[r - (1<<k) + 1][k]);
}

