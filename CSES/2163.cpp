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

struct BIT{
	int b[mxN], n;
    BIT(int sz) {
        n = sz;
    }
    void build() {
        for (int i = 1; i <= n; i++) {
            b[i] += 1;
            int j = i + (i&-i);
            if (j <= n) b[j] += b[i];
        }
    }
	int qry(int i) {
		int res = 0;
        test(i);
		for (; i > 0; i -= (i&-i)) res += b[i];
		return res;
	}
	void upd(int i, int v) {
		for (; i <= n; i += (i&-i)) b[i] += v; 
	}
    int findk(int k) {
        int id = 0, res = 0;
        int mx = __lg(n) + 1;
        for (int i = mx; i >= 0; i--) {
            if ((id | (1<<i)) > n) continue;
            if (res + b[id|(1<<i)] < k) { 
                id = (id | (1<<i));
                res += b[id];
            }
        }
        return id + 1;
    }
};

inline void solve() {
    int n, k;
    cin >> n >> k;

    BIT bit(n);

    bit.build();

    int x = k % n;
    for (int left = n; left >= 1; left--) {
        int res = bit.findk(x);
        cout << (res + 1) << ' ';
        bit.upd(res, -1);
        x += k;
        if (x >= left) x %= left;
    }
}

signed main() {
	IO;	
	solve();	
}
