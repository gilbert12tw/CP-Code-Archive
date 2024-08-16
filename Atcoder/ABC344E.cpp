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

inline void solve() {
    int n; cin >> n;
    map<int, int> nxt, lst;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    for (int i = 0; i < n; i++) {
        if (i != n - 1) nxt[a[i]] = a[i+1];
        if (i != 0) lst[a[i]] = a[i-1];
    }
    nxt[-1] = a[0];
    lst[a[0]] = -1;

    int q; cin >> q;
    while (q--) {
        int o, x, y;
        cin >> o;
        if (o == 1) {
            cin >> x >> y;
            nxt[y] = nxt[x];
            lst[y] = x;
            lst[nxt[y]] = y;
            nxt[x] = y;
        } else {
            cin >> x;
            lst[nxt[x]] = lst[x];
            nxt[lst[x]] = nxt[x];
            nxt[x] = lst[x] = 0;
        }
    }
    int x = nxt[-1];
    cout << x;
    x = nxt[x];
    while (x > 0) {
        cout << ' ' << x;
        x = nxt[x];
    }
}

signed main() {
	IO;	
	solve();	
}
