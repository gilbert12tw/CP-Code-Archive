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

}

signed main() {
	IO;	
    int t; cin >> t;
    //int T; cin >> T;
	//while (T--) solve();	
    map<multiset<int>, vector<int>> mp;
    for (int i = 1; i <= 1000000; i++) {
        multiset<int> mt;
        int res = i * i;
        while (res) {
            mt.insert(res % 10);
            res /= 10;
        }
        if (mt.count(0) == 0) mp[mt].eb(i * i);
    }
    for (auto [st, v] : mp) {
        if (SZ(st) > SZ(v)) continue;
        if (SZ(st) != 11) continue;
        test(SZ(st));
        test(SZ(v));
        cout << "st = ";
        for (int i : st) cout << i << ' ';
        cout << '\n';
        cout << "v = ";
        for (int i : v) cout << i << ' ';
        cout << '\n';
        cout << '\n';
    }
}
