// Treap !!!
mt19937 ran(time(NULL));
uniform_int_distribution<int> dis(0, 5000000);

#define lc(x) tr[x].ls
#define rc(x) tr[x].rs
int root, tot;
struct Treap {
	int ls, rs, pri, sum, val, pa, tsz;	
	Treap() : ls(0), rs(0), sum(0), pa(0), tsz(0) {}
	Treap(int _b) : ls(0), rs(0), pri(ran()), sum(_b), val(_b), pa(0), tsz(1) {}
} tr[mxN];

inline int node(int v) {
	tr[++tot] = Treap(v);
	return tot;
}

void pushup(int x) {
	tr[x].tsz = tr[lc(x)].tsz + tr[rc(x)].tsz + 1;
	tr[x].sum = tr[lc(x)].sum + tr[rc(x)].sum + tr[x].val;
	tr[lc(x)].pa = tr[rc(x)].pa = x;
}

// split by size
void split(int t, int k, int &a, int &b) {
	if (!t) {
		a = b = 0;
		return;
	} else if (tr[lc(t)].tsz + 1 <= k) {
		a = t;
		split(rc(t), k - tr[lc(t)].tsz - 1, rc(a), b);
	} else {
		b = t;	
		split(lc(t), k, a, lc(b));
	}
	pushup(t);
}

int merge(int a, int b) {
	if (!a or !b) return a | b;	
	else if (tr[a].pri > tr[b].pri) {
		rc(a) = merge(rc(a), b);	
		pushup(a);
		return a;
	} else {
		lc(b) = merge(a, lc(b));
		pushup(b);
		return b;
	}
}

int get_rank(int x) {
	int p = x, res = tr[lc(p)].tsz, now = tr[p].pa;	
	while (now) {
		if (p == tr[now].rs) res += tr[lc(now)].tsz + 1;	
		p = now;
		now = tr[now].pa;
	}
	return res+1;
}

int get(int x) {
	while (tr[x].pa) x = tr[x].pa;	
	return x;
}

void pp(int s) {
	if (!s) return;
    pp(lc(s));
    test(s, tr[s].val);
	pp(rc(s));
}
void mprint(int s) { cout << "root = " << s << endl; pp(s);}
/* end of Treap */
