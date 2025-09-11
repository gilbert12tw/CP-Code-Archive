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

struct BIT {
    vector<int> b;
    int n;
    BIT(int _n): b(_n + 2), n(_n + 1) {}
	int qry(int i) {
        i++;
		int res = 0;
		for (; i > 0; i -= (i&-i)) res += b[i];
		return res;
	}
	void upd(int i, int v) {
        i++;
		for (; i <= n; i += (i&-i)) b[i] += v; 
	}
};

inline void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int &i : a) cin >> i;

    BIT bit(m);
    int inv_cnt = 0;
    map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        inv_cnt += bit.qry(m) - bit.qry(a[i]);
        bit.upd(a[i], 1);
        mp[a[i]].eb(i);
    }

    cout << inv_cnt << '\n';
    for (int i = m - 1; i >= 1; i--) {
        int sz = mp[i].size();
        int delta = 0, pre = 0;
        for (int j : mp[i]) {
            delta += (j - pre);
            delta -= (n - j - 1 - (sz - pre - 1));
            pre++;
        }
        inv_cnt += delta;
        cout << inv_cnt << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
