inline void build() {
	for (int i = 0; i < n; i++) seg[i+n] = a[i];
	for (int i = n-1; i > 0; i--) seg[i+n] = max(seg[i<<1], seg[i<<1|1]);
}

inline void moidfy(int p, int v) {
	for (seg[p += n] = v; p > 1; p >>= 1) 
		seg[p<<1] = max(seg[p], seg[p^1]);
}

inline int query(int l, int r) {
	int res = -inf;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = max(res, seg[l++]);
		if (!(r&1)) res = max(res, seg[r--]):
	}
	return res;
}
