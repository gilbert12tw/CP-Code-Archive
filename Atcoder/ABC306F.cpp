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

struct BIT{
	int b[mxN], n;
    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; i++) b[i] = 0;
    }
	int qry(int i) {
		int res = 0;
		for (; i > 0; i -= (i&-i)) res += b[i];
		return res;
	}
	void upd(int i, int v) {
		for (; i <= n; i += (i&-i)) b[i] += v; 
	}
} bit;

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector< vector<int> > a(n, vector<int>(m));
    vector<int> tmp;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            tmp.eb(a[i][j]);
        }
        sort(ALL(a[i]));
    }

    sort(ALL(tmp));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = lb(tmp, a[i][j]) - tmp.begin() + 1;
        }
    }

    int ans = 0;
    bit.init(n * m + 1);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            ans += bit.qry(a[i][j]) + (j + 1) * (n - i - 1);
        }

        for (int j = 0; j < m; j++) {
            bit.upd(a[i][j], 1);
        }
    }

    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
