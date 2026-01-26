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
template <typename... T> void _print(T... args) {
    ((cerr << args << ' '), ...);
    cerr << '\n';
}
#ifdef debug
#define test(args...) _print("[" + string(#args) + "]:", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline void solve() {
    int n; string s;
    cin >> n >> s;
    unordered_map<int, int> mp;
    int cur_sum = 0;
    int pre = 0;
    mp[cur_sum]++;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') { 
            pre += mp[cur_sum];
            cur_sum++;
        }
        if (s[i] == 'B') {
            cur_sum--;
            pre -= mp[cur_sum];
        }
        mp[cur_sum]++;
        ans += pre;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
