inline int dis(pii a, pii b) {
	int xx = a.x - b.x, yy = a.y - b.y;
	return xx * xx + yy * yy;
}

inline int p2(int x) {
	return x * x;
}

struct KDTree {
	int root, tot;
	struct Node {
		int ch[2] = {0};
		pii p;
		Node(pii _p, int ls, int rs): p(_p), ch{ls, rs} {}
		Node(): ch{0, 0}, p(0, 0){}
	} tr[mxN];
	KDTree(): root(0), tot(0) {}

	void insert(int &q, pii u, int isX) {
		if (!q) {
			q = ++tot;
			tr[q] = Node(u, 0, 0);
			return;
		}
		bool isRight = (isX ? u.x > tr[q].p.x : u.y > tr[q].p.y);
		insert(tr[q].ch[isRight], u, isX ^ 1);
	}

  // query the closest pt to goal
	int qry(int u, pii goal, int isX) {
		bool isRight = (isX ? goal.x > tr[u].p.x : goal.y > tr[u].p.y);
		int ans = dis(goal, tr[u].p);
		if (tr[u].ch[isRight]) {
			ans = min(ans, qry(tr[u].ch[isRight], goal, isX ^ 1));
		}
		int t = (isX ? p2(goal.x - tr[u].p.x) : p2(goal.y - tr[u].p.y));
		if (tr[u].ch[isRight^1] and ans > t) {
			ans = min(ans, qry(tr[u].ch[isRight^1], goal, isX ^ 1));
		}
		return ans;
	}
} kdtree;
