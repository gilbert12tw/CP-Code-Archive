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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

struct linear_base {
	int bas[65] = {0}, tm[65] = {0}, len = 0;	
	const int mxL = 60;

    linear_base() {
        memset(tm, -1, sizeof tm);
    }

	void insert(int x, int t) {
		for (int i = mxL; i >= 0; i--) {
			if (get_bit(x, i)) {
				if (bas[i]) { 
                    if (tm[i] < t) {
                        swap(tm[i], t);
                        swap(bas[i], x);
                    }
                    x ^= bas[i];
                } else {
					bas[i] = x;
                    tm[i] = t;
					len++;
					break;
				}
			}
		}
	}

    int check(int x) {
        int mn = inf;
        for (int i = mxL; i >= 0; i--) {
            if (get_bit(x, i)) {
                if (bas[i] == 0) return -1;
                x ^= bas[i];
                mn = min(mn, tm[i]);
            }
        }
        return mn;
    }
};

inline void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), x(q);
    vector<vector<pii>> qry(n + 1, vector<pii>());
    linear_base bases;
    for (int &i : a) cin >> i;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r >> x[i];
        qry[r - 1].eb(l - 1, i);
    }
    
    vector<int> ans(q);
    for (int i = 0; i < n; i++) {
        bases.insert(a[i], i);
        for (auto [l, id] : qry[i]) {
            if (bases.check(x[id]) >= l) {
                ans[id] = 1;
            }
        }
    }

    for (int i : ans) cout << (i ? "Yes\n" : "No\n");
}

signed main() {
	IO;	
	solve();	
}
