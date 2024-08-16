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

const int mxN = 2e5 + 5;

int n, q;
int a[mxN];
vector<int> disc;

class query {
public:
    int l, r, k, id;
    query() { l = r = k = id = 0;}
    query(int _l, int _r, int _k, int _id) { 
        l = _l;
        r = _r;
        k = _k;
        id = _id;
    }
};

class BIT{
public:
	int b[mxN] = {0};
    vector<int> tmp;

	int qry(int i) {
		int res = 0;
		for (; i > 0; i -= (i&-i)) res += b[i];
		return res;
	}

	void upd(int i, int v) {
		for (; i < mxN; i += (i&-i)) b[i] += v, tmp.eb(i); 
	}

    void clear() {
        for (int i : tmp) b[i] = 0;
        tmp.clear();
    }
};

BIT bit;
int ans[mxN];
void bs(vector<query> &op, vector<int> &num, int l, int r) {
    if (l == r) {
        for (auto [a, b, k, id] : op) {
            ans[id] = l;
        }
        return;
    }

    int mid = (l+r) >> 1;
    vector<query> ql, qr;
    vector<int> nl, nr;

    for (int i : num) {
        if (a[i] <= mid) { 
            bit.upd(i, 1);
            nl.eb(i);
        }
        else nr.eb(i);
    }

    for (auto [a, b, k, id] :  op) {
        int res = bit.qry(b) - bit.qry(a - 1);
        if (res >= k) ql.eb(a, b, k, id);
        else qr.eb(a, b, k - res, id);
    }

    bit.clear();

    bs(ql, nl, l, mid);
    bs(qr, nr, mid+1, r);
}

inline void solve() {
    cin >> n >> q;
    vector<int> num;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        disc.eb(a[i]);
        num.eb(i);
    }
    sort(ALL(disc));
    uni(disc);
    for (int i = 1; i <= n; i++) a[i] = lb(disc, a[i]) - disc.begin() + 1;

    vector<query> qry;
    for (int i = 0; i < q; i++) {
        int l, r, k; 
        cin >> l >> r >> k;
        qry.pb({l, r, k, i + 1});
    }
    bs(qry , num, 1, SZ(disc));

    for (int i = 1; i <= n; i++) cout << disc[ans[i]-1] << '\n';
}

signed main() {
	IO;	
	solve();	
}
