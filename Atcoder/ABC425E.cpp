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

int T, M;
int C[5001][5001];

inline void solve() {
    int n;
    cin >> n;
    vector<int> c(n);
    int ans = 1, sum = 0;
    for (int &i : c) { 
        cin >> i;
        sum += i;
    }
    for (int i : c) {
        ans = (ans * C[sum][i]) % M;
        sum -= i;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
    cin >> T >> M;
    
    int n = 5000;
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1]);
            if (C[i][j] >= M) C[i][j] -= M;
        }
    }

	while (T--) solve();	
}
