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
#define mod 998244353
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

int mat[26][26];

inline void solve(int cs) {
    string s; int k;
    cin >> s >> k;
    int n = SZ(s);
    vector<vector<int>> dp(10, vector<int>(n + 1));
    vector<int> sum(n + 1);
    
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '?') {
        } else {
            int num = (s[i - 1] - '0');
            for (int j = 0; j < 10; j++) {
                dp[num][i] = (dp[num][i] + dp[j][i-1]) % mod;
                if (mat[j][num] && j 
            }
        }
    }


    cout << "Case #" << cs << ": " << ans << '\n';
}

signed main() {
	IO;	
    for (int i = 0; i < 10; i++) {
        mat[1][i] = 1;
        if (i < 7) mat[2][i] = 1;
    }
    int T; cin >> T;
	for (int i = 1; i <= T; i++) solve(i);	
}
