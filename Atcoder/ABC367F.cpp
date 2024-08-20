#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
#define vi vector<int>
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
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }


mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dis(0, 200000);

int hsh_tab[200005];
struct Segment_Tree {
#define ls (x<<1)
#define rs ((x<<1)|1)
#define mid ((l+r)>>1)
    int n;
    vector<int> seg;
    Segment_Tree(int _n): n(_n), seg(_n * 4) {}

    inline int op(int a, int b) {
        return (a + b) % mod;
    }

    void up(int x) {
        seg[x] = op(seg[ls], seg[rs]);
    }

    void build(int l, int r, int x, vector<int> &a) {
        if(l == r) {
            seg[x] = a[l];
            return;
        }
        build(l, mid, ls, a); build(mid+1, r, rs, a);
        up(x);
    }

    int query(int a, int b, int l, int r, int x) {
        //test(a, b, seg[x]);
        if(a <= l and r <= b) return seg[x];
        int res = 0;
        if(a <= mid) res = query(a, b, l, mid, ls);
        if(b > mid) res = op(res, query(a, b, mid+1, r, rs));
        return res;
    }
    int query(int a, int b) { return query(a, b, 0, n - 1, 1); }
};


const int mxN = 1e8 + 5;
int np[mxN];
vector<int> prime;
void sieve(int n) {
	for(int i = 2; i <= n; i++) {
		if(np[i] == 0) np[i] = i, prime.eb(i);
		for(int j : prime) {
			if(i * j > n) break;
			np[i * j] = j;
			if(np[i] == j) break;
		}
	}
}

inline void solve() {
    int n, q;
    cin >> n >> q;
    sieve(50000000);
    for (int i = 0; i <= 200000; i++) {
        hsh_tab[i] = prime[dis(gen)];
    }

    vector<int> a(n), b(n);
    for (int &i : a) { cin >> i; i = hsh_tab[i]; }
    for (int &i : b) { cin >> i; i = hsh_tab[i]; }
    Segment_Tree seg1(n), seg2(n);
    seg1.build(0, n - 1, 1, a);
    seg2.build(0, n - 1, 1, b);

    while (q--) {
        int l, r, L, R;
        cin >> l >> r >> L >> R;
        l--, r--, L--, R--;
        test(seg1.query(l, r), seg2.query(L, R));
        if (seg1.query(l, r) == seg2.query(L, R)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

signed main() {
	IO;	
	solve();	
}
