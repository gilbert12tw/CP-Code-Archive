#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<bitset>
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

struct Line {
	int a, b;	
	int operator () (int x) {
		return a * x + b;
	}
    Line (int _a, int _b): a(_a), b(_b) {};
    Line (): a(0), b(-INF) {};
} seg[mxN];
const int mxR = 5e5 + 5;

#define ls (id<<1)
#define rs (ls|1)
void insert(Line t, int l = 0, int r = mxR, int id = 1) {
	int mid = (l+r) >> 1;
	if (t(mid) > seg[id](mid)) swap(t, seg[id]);
	if (l == r)  return;
	if (t(l) > seg[id](l)) insert(t, l, mid, ls);
	if (t(r) > seg[id](r)) insert(t, mid+1, r, rs);
}

void modify(Line t, int a, int b, int l = 0, int r = mxR, int id = 1) {
	if (a <= l and r <= b) { 
		insert(t, l, r, id);	
		return;
	}
	int mid = (l + r) >> 1;
	if (a <= mid) modify(t, a, b, l, mid, ls);
	if (b > mid) modify(t, a, b, mid+1, r, rs);
}

int query(int p, int l = 0, int r = mxR, int id = 1) {
	if (l == r) return seg[id](p);
	int mid = (l+r)>>1;
	if (p <= mid) return max(query(p, l, mid, ls), seg[id](p));
	else return max(query(p, mid+1, r, rs), seg[id](p));
}


inline void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> c(n), pre(n), dp(n);
    for (int &i : c) cin >> i;
    reverse(ALL(c));

    for (int i = 0; i < n; i++) {
        if (!i) pre[i] = c[i];
        else pre[i] = pre[i-1] + c[i];
    }
    
    modify(Line(-2, -1), 0, k - 1);
    for (int i = 0; i < n; i++) {
        dp[i] = pre[i] - i * i + query(i);
        modify(Line(2 * i, dp[i] - i * i), i + 1, i + k);
    }
    cout << dp[n-1] - pre[n-1] << '\n';
}

signed main() {
	IO;	
	solve();	
}
