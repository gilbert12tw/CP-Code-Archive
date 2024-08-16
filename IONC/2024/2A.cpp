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
#define MOD 998244353
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


struct BIT{
    vector<int> b;
    int n;
    BIT(int _n): b(_n + 1), n(_n) {}
	int qry(int i) {
		int res = 0;
		for (; i > 0; i -= (i&-i)) res += b[i];
		return res;
	}
	void upd(int i, int v) {
		for (; i <= n; i += (i&-i)) b[i] += v; 
	}
};

inline void solve() {
    int n;
    cin >> n;
    vecotr<int> a(n), b(n), c(n);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;
    for (int &i : c) cin >> i;

    int q; cin >> q;
    vecotor<array<int, 4>> qry(q);
    for (int i = 0; i < q; i++) {
        cin >> qry[i][0] >> qry[i][1] >> qry[i][2];
        qry[i][3] = i;
    }
    
    BIT bit(n);
    
}

signed main() {
	IO;	
	solve();	
}
