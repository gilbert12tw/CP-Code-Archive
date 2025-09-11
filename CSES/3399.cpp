#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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
    int n, a, b;
    cin >> n >> a >> b;
    if (a == 0 && b == 0) {
        cout << "YES\n";
        for (int i = 1; i <= n; i++) cout << i << " \n"[i == n];
        for (int i = 1; i <= n; i++) cout << i << " \n"[i == n];
        return;
    }
    if (a + b > n || a >= n || b >= n || a == 0 || b == 0) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";

    vector<int> ansb(n);
    iota(ALL(ansb), 1);
    for (int i = n - a + 1, cnt = 0; cnt < a + b; cnt++) {
        ansb[i-1] = cnt + (n - a - b + 1);
        //test(i, n - a - b + 1, cnt);
        i++;
        if (i > n) i = n - a - b + 1;
    }

    for (int i = 1; i <= n; i++) cout << i << " \n"[i == n];
    for (int i = 0; i < n; i++) cout << ansb[i] << " \n"[i == n - 1];
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
