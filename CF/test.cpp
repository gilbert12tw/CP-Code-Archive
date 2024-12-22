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

map<int, int> dp;
int cal(int m, int len) {
    if (dp.find(len) != dp.end()) return dp[len];
    int lft = len / 2 - (len % 2 == 0);
    int rgt = len / 2;
    if (lft >= m && rgt >= m) return dp[len] = 1 + cal(m, lft) + cal(m, rgt);
    return 0;
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    n -= 2;
    if (n == 0) {
        cout << m + 2 << '\n';
        return;
    }

    int l = n * m, r = (n + 1) * (m + 1) * 2;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (cal(m, mid) >= n) r = mid;
        else l = mid + 1;
    }
    cout << l + 2 << '\n';
}

signed main() {
	IO;	
	solve();	
}
