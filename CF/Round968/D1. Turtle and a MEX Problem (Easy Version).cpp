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

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> l(n), a(n, -1), b(n, -1);

    map<int, int> dp;
    map<int, vector<int>> G;
    set<int> st;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int l; cin >> l;
        set<int> v;
        while (l--) {
            int x; cin >> x;
            v.insert(x);
        }
        // Mex
        for (int j = 0; ; j++) {
            if (v.count(j)) continue;
            if (a[i] == -1) {
                a[i] = j;
            } else if (b[i] == -1) {
                b[i] = j;
            } else {
                break;
            }
        }
        test(a[i], b[i]);
        G[a[i]].eb(b[i]);
        st.insert(a[i]);
        mx = max(mx, b[i]);
    }

    function<int(int)> dfs = [&](int u) {
        if (dp.find(u) == dp.end()) dp[u] = u;
        else return dp[u];
        int res = u;
        for (int v : G[u]) {
           res = max(res, dfs(v)); 
        }
        return dp[u] = res;
    };

    int ans = 0, prv = 0;
    st.insert(m);
    //for (int i : st) {
        //ans += dfs(i);
    //}
    test(mx);
    if (m <= mx) {
        ans = mx * (m + 1);
    } else {
        ans = mx * (mx + 1) + (mx + m + 1) * (m - mx) / 2;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) { 
        test(T);
        solve();	
    }
}
