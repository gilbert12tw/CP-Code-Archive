#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define pii pair<int, int>
//#define int long long
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
#define NONE 100000

int n, m;

// Treap !!!
mt19937 ran(time(NULL));

#define lc(x) tr[x].ls
#define rc(x) tr[x].rs
int tot;
struct Treap {
	int ls, rs, pri, val, sum, pre, suf, mx, reverse_tag, same_tag, tsz;	
	Treap() {
        ls = rs = pri = val = sum = pre = suf = reverse_tag = same_tag = tsz = 0;
        mx = -inf;
        same_tag = NONE;
    }
	Treap(int _b) : ls(0), rs(0), pri(ran()), val(_b), sum(_b), pre(max(0, _b)), suf(max(0, _b)), mx(_b), reverse_tag(0), same_tag(NONE), tsz(1) {}
} tr[3000005];

inline int node(int v) {
	tr[++tot] = Treap(v);
	return tot;
}

void push_tag(int x, int reverse_tag, int same_tag) {
    if (same_tag != NONE) {
        tr[x].val = same_tag;
        tr[x].sum = tr[x].val * tr[x].tsz;
        tr[x].pre = max(0, tr[x].sum);
        tr[x].suf = max(0, tr[x].sum);
        tr[x].mx = max(tr[x].val, tr[x].sum);
        tr[x].same_tag = same_tag;
    }
    if (reverse_tag) {
        swap(tr[x].pre, tr[x].suf);
        swap(lc(x), rc(x));
        tr[x].reverse_tag ^= 1;
    } 
}

void down(int x) {
    if (lc(x)) push_tag(lc(x), tr[x].reverse_tag, tr[x].same_tag);
    if (rc(x)) push_tag(rc(x), tr[x].reverse_tag, tr[x].same_tag);
    tr[x].reverse_tag = 0;
    tr[x].same_tag = NONE;
}

void pushup(int x) {
    if (!x) return;
	tr[x].tsz = tr[lc(x)].tsz + tr[rc(x)].tsz + 1;
	tr[x].sum = tr[lc(x)].sum + tr[rc(x)].sum + tr[x].val;
    tr[x].pre = max({0, tr[lc(x)].pre, tr[lc(x)].sum + tr[x].val + tr[rc(x)].pre});
    tr[x].suf = max({0, tr[rc(x)].suf, tr[rc(x)].sum + tr[x].val + tr[lc(x)].suf});
    tr[x].mx = max({tr[lc(x)].suf + tr[x].val + tr[rc(x)].pre, tr[x].val});
    if (lc(x)) tr[x].mx = max(tr[x].mx, tr[lc(x)].mx);
    if (rc(x)) tr[x].mx = max(tr[x].mx, tr[rc(x)].mx);
}

void split(int t, int k, int &a, int &b) { // [1, k] (k, n]
	if (!t) {
		a = b = 0;
		return;
	} 
    down(t);
    if (tr[lc(t)].tsz + 1 <= k) {
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

void pp(int s) {
	if (!s) return;
    down(s);
	pp(lc(s)); 
    cout << tr[s].val << ' ';
    pp(rc(s));
}
// void mprint(int s) {
//     cout << "[test treap]\n";
//     test(tr[s].tsz, tr[s].sum, tr[s].mx);
//     pp(s); cout << endl;
// }
/* end of Treap */


inline void solve() {
    cin >> n >> m;
    int root = 0;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        root = merge(root, node(a));         
    }

    while (m--) {
        string s; cin >> s;
        int pos, tt, val;
        int a, b, c;
        if (s[0] == 'I') {
            cin >> pos >> tt;
            int tmp_root = 0;
            while (tt--) {
                int x; cin >> x;
                tmp_root = merge(tmp_root, node(x));
            }
            split(root, pos, a, b);
            root = merge(a, merge(tmp_root, b));
        } else if (s[0] == 'D') {
            cin >> pos >> tt;
            int l = pos, r = pos + tt - 1;
            split(root, r, b, c);
            split(b, l - 1, a, b);
            root = merge(a, c);
        } else if (s[2] == 'K') {
            cin >> pos >> tt >> val;
            int l = pos, r = pos + tt - 1;
            split(root, r, b, c);
            split(b, l - 1, a, b);

            down(b);
            push_tag(b, 0, val);
            //down(b);

            root = merge(a, merge(b, c)); 
        } else if (s[0] == 'R') {
            cin >> pos >> tt;
            int l = pos, r = pos + tt - 1;
            split(root, r, b, c);
            split(b, l - 1, a, b);

            down(b);
            push_tag(b, 1, NONE);
            // down(b);
            root = merge(a, merge(b, c));
        } else if (s[0] == 'G') {
            cin >> pos >> tt;
            int l = pos, r = pos + tt - 1;
            split(root, r, b, c);
            split(b, l - 1, a, b);
    
            cout << tr[b].sum << '\n';

            root = merge(a, merge(b, c));
        } else {
            cout << tr[root].mx << '\n';
        }
        //mprint(root);
    }
    //mprint(root);
}

signed main() {
	IO;	
	solve();	
}
