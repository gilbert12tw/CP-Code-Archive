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

const int THRES = 10000;
bitset<THRES> mat[100001];



inline void solve() {
    int n, q; 
    cin >> n >> q;

    int last_ans = 0;
    while (q--) {
        int a, b, c;
        int o, u, v;
        cin >> a >> b >> c;
        o = 1 + (a * (1 + last_ans) % MOD) % 2;
        u = 1 + (b * (1 + last_ans) % MOD) % n;
        v = 1 + (c * (1 + last_ans) % MOD) % n;

        if (o == 1) {
            mat[u][v] = mat[v][u] = 1;
        } else {
            int ans = (mat[u] & mat[v])._Find_first();
            if (ans == -1 || ans > n) ans = 0;
            cout << ans << '\n';
            last_ans = ans;
        }
    }

}

signed main() {
	IO;	
	solve();	
}
