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
    int h, w;
    cin >> h >> w;
    vector<int> a(h), b(h);
    for (int i = 0; i < h; i++) {
        cin >> a[i] >> b[i];
    }

    set<pii> dp;
    multiset<int> dis;

    auto erase = [&](int x, int d) {
        dis.erase(dis.find(d));
        dp.erase(mkp(x, d));
    };

    auto insert = [&](int x, int d) {
        auto it = dp.lower_bound(mkp(x, -1));
        if (it != dp.end() && it->first == x) {
            if (it->second > d) {
                erase(it->first, it->second);
            } else {
                return;
            }
        }
        dp.insert(mkp(x, d));
        dis.insert(d);
    };

    for (int i = 1; i <= w; i++) {
        insert(i, 0);
    }

    for (int i = 0; i < h; i++) {
        auto it = dp.lower_bound(mkp(a[i], -1));
        while (it != dp.end() && it->first <= b[i]) {
            if (next(it) == dp.end() || next(it)->first > b[i]) {
                if (b[i] != w) {
                    insert(b[i] + 1, it->second + b[i] - it->first + 1);
                }
            }
            dis.erase(dis.find(it->second));
            it = dp.erase(it);
        }
        if (dis.empty()) cout << -1 << '\n';
        else cout << i + 1 + *dis.begin() << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
