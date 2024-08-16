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

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dis(-1000000000000, 1000000000000);

inline void solve() {
    map<int, int> cnt;
    map<pii, int> edge;
    vector<pii> tmp;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        if (edge.count(mkp(u, v)) == 0) {
            edge[mkp(u, v)] = dis(gen);
        }
        tmp.eb(u, v);
    }
    
    vector<int> ran(n + 10);
    for (int i = 1; i <= n; i++) ran[i] = dis(gen);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        map<pii, int> viscnt;
        int hsh = 0;
        for (int j = i; j < n; j++) {
            hsh += (edge[tmp[j]] + ran[viscnt[tmp[j]]]);
            ans += (cnt[hsh]++);
            viscnt[tmp[j]]++;
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
