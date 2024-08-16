// persistent segment tree
struct persistent_segment {
	const int mxN = 2e5 + 5;
	int ls[mxN * 30], rs[mxN * 30], seg[mxN * 30], edit[mxN], tot, etot;
	#define mid ((l+r)>>1)

	inline void up(int id) {
		seg[id] = seg[ls[id]] + seg[rs[id]];
	}

	inline void copy(int id, int p) {
		ls[id] = ls[p]; rs[id] = rs[p]; seg[id] = seg[p];
	}

	void build(int &id, int l = 1, int r = n) {
		if (!id) id = ++tot;
		if (l == r) {
			seg[id] = t[l];	
			return;
		}
		build(ls[id], l, mid); build(rs[id], mid + 1, r);
		up(id);
	}

	void modify(int &id, int pos, int v, int l = 1, int r = n) {
		int p = id;
		id = ++tot;
		if (l == r) {
			seg[id] = v;
			return;
		}
		copy(id, p); 
		if (pos <= mid) modify(ls[id], pos, v, l, mid);
		else modify(rs[id], pos, v, mid + 1, r);
		up(id);
	}

	int query(int ed, int a, int b, int l = 1, int r = n) {
		if (a <= l and r <= b) return seg[ed];
		int res = 0;
		if (a <= mid) res = query(ls[ed], a, b, l, mid);
		if (b > mid) res += query(rs[ed], a, b, mid+1, r);
		return res;
	}
};
