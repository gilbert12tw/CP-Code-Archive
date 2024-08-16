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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), x(k + 1), pre(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }
    for (int i = 1; i <= k; i++) {
        cin >> x[i];
        x[i]++;
    }
    
    vector<int> ans(k + 1, pre[n]);
    vector<int> mp(k + 1), lst(n + 1);
    for (int i = 1; i <= n; i++) {
        lst[i] = mp[a[i]];
        mp[a[i]] = i; 
    }
    vector<int> add(n + 1);
    for (int i = n; i >= 1; i--) {
        int xx = x[a[i]] + add[i];
        if (i - lst[i] >= xx) {
            ans[a[i]] -= (pre[i] - pre[i - xx]);
        } else {
            ans[a[i]] -= (pre[i] - pre[lst[i]]);
            int lft = xx - (i - lst[i]);
            add[lst[i]] += lft;
        }
    }
    for (int i = 1; i <= k; i++) cout << ans[i] << '\n';
}

signed main() {
	IO;	
	solve();	
}
