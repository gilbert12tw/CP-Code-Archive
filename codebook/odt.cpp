struct node {
	int l, r, v;
	node(int il, int ir, int iv) : l(il), r(ir), v(iv) {}
	bool operator < (const node a) const {
		return l < a.l;
	}
};
set<node> odt;

auto split(int x) {
	auto it = prev(odt.upper_bound((node){x, 0, 0}));
	if(it->l == x) return it;
	int l = it->l, r = it->r, v = it->v;
	odt.erase(it);
	odt.insert((node){l, x - 1, v});
	return odt.insert((node){x, r, v}).F;
}

void add(node a) {
	auto itr = split(a.r + 1), itl = split(a.l);
	while(itl != itr) {
		itl = odt.erase(itl);
	}
	odt.insert(a);
}

