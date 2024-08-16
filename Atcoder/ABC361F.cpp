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

int n; 
int pow(int a, int b) {
    int res = 1;
    while (b--) { 
        res *= a;
        if (res > n) {
            return n + 1;
        }
    }
    return res;
}
int bs(int x) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (pow(mid, x) >= n) r = mid;
        else l = mid + 1;
    }
    return l - 1;
}

inline void solve() {
    cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    
    vector<int> dp(100);
    for (int i = 60; i >= 2; i--) {
        int l, r;
        l = 2;
        r = bs(i);
        dp[i] = max(0ll, (r - l + 1));
        for (int j = i + i; j <= 60; j += i) {
            dp[i] -= dp[j];
        }
    }
    int ans = 1;
    for (int i = 2; i <= 60; i++) ans += dp[i];
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
