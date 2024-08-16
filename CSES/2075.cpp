#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - x.begin())
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 2e6 + 5;

// Treap !!!
mt19937 ran(time(NULL));
uniform_int_distribution<int> dis(0, 10000);

#define lc(x) tr[x].ls
#define rc(x) tr[x].rs
int root, tot;
struct Treap {
	int ls, rs, pri, pa, tsz, tag;	
	Treap() : ls(0), rs(0),  pa(0), tsz(0), tag(0) {}
} tr[mxN];

inline int node(int i) {
	tr[i] = Treap();
    tr[i].pri = ran();
    tr[i].tsz = 1;
	return i;
}

void toggle(int i) {
    swap(lc(i), rc(i));
    tr[i].tag ^= 1;
}

void down(int x) {
   if (tr[x].tag) {
       toggle(lc(x));
       toggle(rc(x));
       tr[x].tag = 0;
   } 
}

void pushup(int x) {
	tr[x].tsz = tr[lc(x)].tsz + tr[rc(x)].tsz + 1;
	tr[lc(x)].pa = tr[rc(x)].pa = x;
}

void split(int t, int k, int &a, int &b) {
    if (t) down(t);
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
        down(a);
		rc(a) = merge(rc(a), b);	
		pushup(a);
		return a;
	} else {
        down(b);
		lc(b) = merge(a, lc(b));
		pushup(b);
		return b;
	}
}

vector<int> get(int x) {
    vector<int> path;
    path.eb(x);
	while (tr[x].pa) { 
        x = tr[x].pa;	
        path.eb(x);
    }
	return path;
}

int get_rank(int x) {
    vector<int> tmp = get(x);
    reverse(ALL(tmp));
    for (int i : tmp) down(i);

	int p = x, res = tr[lc(p)].tsz, now = tr[p].pa;	
	while (now) {
		if (p == tr[now].rs) res += tr[lc(now)].tsz + 1;	
		p = now;
		now = tr[now].pa;
	}
	return res+1;
}

void pp(int s) {
	if (!s) return;
    pp(lc(s));
    test(s);
	pp(rc(s));
}
void mprint(int s) { cout << "root = " << s << endl; pp(s);}
/* end of Treap */


inline void solve() {
    int n; cin >> n;
    int root = 0;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        root = merge(root, node(a));
    }

    //mprint(root);
    //for (int i = 1; i <= n; i++) test(i, get_rank(i));
    
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
        int l = i, r = get_rank(i);
        cout << l << ' ' << r << '\n';
        int a, b, c;
        split(root, r, b, c);
        split(b, l - 1, a, b);
        toggle(b);
        root = merge(a, merge(b ,c));
        tr[root].pa = 0;
    }
}

signed main() {
	IO;	
	solve();	
}
