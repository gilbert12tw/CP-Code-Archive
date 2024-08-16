#include<bits/stdc++.h>
#define ll Loli
#define inf 1e9
#define INF 1e18
#define MOD 1000000007
#define mod 998244353
#define int long long
#define eb emplace_back
#define pb push_back
#define push emplace
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pii pair<int, int>
#define F first
#define S second
#define get_bit(x, i) ((x>>i)&1) 
#define mkp make_pair
#define de(x) cout << #x << " = " << x << '\n'
#define deb(x, y) cout << #x << " = " << x << " " << #y << " = " << y << '\n'

using namespace std;
const int mxN = 1e5 + 1;

mt19937 ran(time(NULL));
int root, tot, nd[mxN];
struct Treap {
	int ls, rs, pri, tsz, id, pa;
	Treap(): ls(0), rs(0), tsz(0) {}	
	Treap(int v): ls(0), rs(0), pri(ran()), tsz(1), id(v), pa(0) {}
} tr[mxN];

class A{
public:
    int a, b;
};

class B : A {
public:
    void printB() {
        cout << a << ' ' << b << '\n';
    }
};

inline int New(int v) {
	tr[++tot] = Treap(v);	
	return tot;
}

#define lc(x) tr[x].ls
#define rc(x) tr[x].rs
inline void up(int x) {
	tr[x].tsz = tr[lc(x)].tsz + tr[rc(x)].tsz + 1;
	tr[lc(x)].pa = tr[rc(x)].pa = x;
}

int merge(int a, int b) {
	if (!a or !b) return a | b;
	else if (tr[a].pri > tr[b].pri) {
		rc(a) = merge(rc(a), b);	
		up(a);
		return a;
	} else {
		lc(b) = merge(a, lc(b));
		up(b);
		return b;
	}
}

void split(int t, int k, int &a, int &b) {
	if (!t) {
		a = b = 0;
		return;
	} else if (tr[lc(t)].tsz + 1 <= k) {
		a = t;
		split(tr[t].rs, k - tr[lc(t)].tsz - 1, tr[a].rs, b);
	} else {
		b = t;
		split(tr[t].ls, k, a, tr[b].ls);
	}
	up(t);
}

int get_rank(int x) {
	int p = nd[x], res = tr[lc(p)].tsz, now = tr[p].pa;	
	while (p != root) {
		if (p == tr[now].rs) res += tr[lc(now)].tsz + 1;	
		p = now;
		now = tr[now].pa;
	}
	return res;
}

int query(int t, int k) {
	if (tr[lc(t)].tsz + 1 == k) return tr[t].id;	
	else if (tr[lc(t)].tsz + 1 < k) return query(rc(t), k - tr[lc(t)].tsz - 1);
	else return query(lc(t), k);
}

int n, m;
inline void solve() {
	cin >> n >> m;	
	for (int i = 1; i <= n; i++) {
		int p; cin >> p;
		root = merge(root, New(p));
		nd[p] = tot;
	}

	while (m--) {
		string o;	
		int s, t, a, b, c;
		cin >> o >> s;
		if (o[0] == 'I') {
			cin >> t;	
			int rk = get_rank(s);
			split(root, rk + 1, b, c);
			split(b, rk, a, b);
			root = merge(a, c);
			split(root, rk + t, a, c);
			root = merge(a, merge(b, c));
		} else if (o[0] == 'T') {
			int rk = get_rank(s);	
			split(root, rk + 1, b, c);
			split(b, rk, a, b);
			root = merge(b, merge(a, c));
		} else if (o[0] == 'B') {
			int rk = get_rank(s);	
			split(root, rk + 1, b, c);
			split(b, rk, a, b);
			root = merge(merge(a, c), b);
		} else if (o[0] == 'A') {
			cout << get_rank(s) << '\n';		
		} else {
			cout << query(root, s) << '\n';	
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0);	
	solve();
}
