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

const int mxN = 1e5 + 5;

#define ls x<<1
#define rs x<<1|1
#define mid ((l+r)>>1)

int n, m;
int a[mxN];
int mx[mxN * 4], sum[mxN * 4];
void up(int x) {
	mx[x] = max(mx[ls], mx[rs]);
    sum[x] = sum[ls] + sum[rs];
}

void build(int l = 1, int r = n, int x = 1) {
	if(l == r) {
		mx[x] = a[l];
        sum[x] = a[l];
		return;
	}
	build(l, mid, ls); build(mid+1, r, rs);
	up(x);
}

void modify(int p, int v, int l = 1, int r = n, int x = 1) {
	if(l == r) {
		mx[x] = sum[x] = v;
		return;
	}
	if(p <= mid) modify(p, v, l, mid, ls);
	else modify(p, v, mid+1, r, rs);
	up(x);
}

void modmod(int a, int b, int p, int l = 1, int r = n, int x = 1) {
    if (l == r) {
        mx[x] %= p;
        sum[x] %= p;
        return;
    }
    if (a <= mid && mx[ls] >= p) modmod(a, b, p, l, mid, ls);
    if (b > mid && mx[rs] >= p) modmod(a, b, p, mid+1, r, rs);
    up(x);
}

int query(int a, int b, int l = 1, int r = n, int x = 1) {
	if(a <= l and r <= b) return sum[x];
	int res = 0;
	if(a <= mid) res = query(a, b, l, mid, ls);
	if(b > mid) res += query(a, b, mid+1, r, rs);
	return res;
}

inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build();
    while (m--) {
        int o, l, r, x;
        cin >> o;
        if (o == 1) {
            cin >> l >> r;
            cout << query(l, r) << '\n';
        } else if (o == 2) {
            cin >> l >> r >> x;
            modmod(l, r, x);
        } else {
            cin >> l >> x;
            modify(l, x);
        }
    }
}

signed main() {
	IO;	
	solve();	
}
