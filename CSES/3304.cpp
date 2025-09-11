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
    int n, q;
    cin >> n >> q;
    vector<vector<int>> jp(n, vector<int>(20, -1));
    vector<int> a(n);
    for (int &i : a) cin >> i;
    vector<int> stk;
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && a[stk.back()] <= a[i]) stk.pop_back();
        if (!stk.empty())
            jp[i][0] = stk.back();
        stk.eb(i);

        for (int j = 1; j < 20; j++) {
            if (~jp[i][j-1])
                jp[i][j] = jp[jp[i][j-1]][j-1];
        }
    }


    while (q--) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        a--, b--;
        for (int i = 19; i >= 0; i--) {
            if (jp[a][i] != -1 && jp[a][i] <= b) {
                a = jp[a][i];
                ans += (1<<i);
            }
        }
        cout << ans+1 << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
