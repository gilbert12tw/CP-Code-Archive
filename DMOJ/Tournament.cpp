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
    int n; cin >> n;
    vector<int> a(n - 1);
    vector<int> appr(n + 1);
    for (int &i : a) cin >> i, appr[i] = 1;
    int ms = 0;
    for (int i = 1; i <= n; i++) {
        if (!appr[i]) ms = i;
    }

    vector<pii> tour(2 * (n + 1) + 5); // (sum, winer)

    a.insert(a.begin(), ms);

    #define ls (x<<1)
    #define rs ((x<<1)|1)
    auto up = [&](int x) {
        tour[x] = mkp((tour[ls].S - tour[rs].S) * (tour[ls].S - tour[rs].S) + tour[ls].F + tour[rs].F,
                      max(tour[ls].S, tour[rs].S));
    };
    auto modify = [&](int x, int v) {
        int id = n + x - 1;
        //test(x, id);
        tour[id] = mkp(0, v);
        id >>= 1;
        while (id) {
            up(id);
            id >>= 1;
            //test(id, tour[id].F, tour[id].S);
        }
    };
    for (int i = 1; i <= n; i++) { 
        modify(i, a[i-1]);
    }
    for (int i = 1; i <= n; i++) {
        cout << tour[1].F << ' ';
        swap(a[i-1], a[i]);
        modify(i, a[i-1]);
        modify(i+1, a[i]);
    }
}

signed main() {
	IO;	
	solve();	
}
