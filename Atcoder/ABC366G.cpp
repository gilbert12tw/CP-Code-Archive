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

struct linear_base {
	int bas[65] = {0}, len = 0;	
	const int mxL = 61;
	void insert(int x) {
        for (int i = 0; i < mxL; i++) {
			if (get_bit(x, i)) {
				if (bas[i]) x ^= bas[i];
				else {
					bas[i] = x;
					len++;
					break;
				}
			}
		}
	}
	void elimination() {
		for (int i = 0; i < mxL; i++) {
			if (!bas[i]) continue;
			for (int j = i + 1; j <= mxL; j++) {
				if (get_bit(bas[j], i)) bas[j] ^= bas[i];
			}
		}
	}
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    linear_base bs;
    for (int i = 0; i < n; i++) {
        int x = 0;
        for (int j : adj[i]) {
            x |= (1LL<<j);
        }
        test(x);
        if (x > 0) bs.insert(x);
    }
    test(bs.len);

    vector<int> a(n);
    bs.elimination();
    for (int i = n - 1; i >= 0; i--) {
        if (!bs.bas[i]) {
            a[i] = (1LL<<i);
            continue;
        }
        test(i, bs.bas[i]);
        int res = 0;
        for (int j = i + 1; j < n; j++) {
            if (get_bit(bs.bas[i], j)) {
                res ^= a[j];
                test(j, a[j]);
            }
        }
        a[i] = res;
    }
    int ok = 1;
    for (int i = 0; i < n; i++) {
        int res = 0;
        for (int j : adj[i]) { 
            if (a[j] == 0) ok = 0;
            res ^= a[j];
        }
        if (res != 0) ok = 0;
    }
    if (!ok) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    for (int i : a) cout << i << ' ';
}

signed main() {
	IO;	
	solve();	
}
