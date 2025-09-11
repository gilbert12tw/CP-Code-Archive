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

int dp[15][15][15], mp[15][15][15];
inline void solve() {
    int n; cin >> n; 
    memset(mp, 0, sizeof(mp));
    for (int i = 0; i < n; i++) {
        int x, y, z, v; 
        cin >> x >> y >> z >> v;
        mp[x][y][z] += v;
    }

    //memset(dp, -0x3f, sizeof(dp));

    dp[10][1][1] = 0;
    int mx = 0;
    for (int i = 10; i >= 1; i--) {
        for (int j = 1; j <= 10; j++) {
            for (int k = 1; k <= 10; k++) {
                dp[i][j][k] = max({dp[i+1][j][k], dp[i][j-1][k], dp[i][j][k-1]}) + mp[i][j][k];
                mx = max(mx, dp[i][j][k]);
                //test(dp[i][j][k]);
            }
        }
    }
    cout << mx << '\n';
}

inline void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
}

signed main() {
    setIO("commandos");     
    int T; cin >> T;
	while (T--) solve();	
}
