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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    int p = (1 << (n / 2));
    int msk = p - 1;

    sort(ALL(a));
    reverse(ALL(a));
 
    vector<vector<int>> dp(n, vector<int>(p));
    dp[0][0]++;
    dp[0][a[0] & msk]++;
    for (int i = 0; i < n - 1; i++) {
        dp[i+1] = dp[i];
        for (int j = 0; j < p; j++) {
            dp[i+1][(j + a[i+1]) & msk] += dp[i][j];
        }
    }
 
    int mx_sum = 0;
    for (int i = 0; i < p; i++) {
        if (dp[n-1][i] >= dp[n-1][mx_sum]) {
            mx_sum = i;
        }
    }
 
    unordered_map<int, int> mp;

    auto print_ans = [&](int bit, int bit2) -> void {
        int ad = bit & bit2;
        bit ^= ad; bit2 ^= ad;
        cout << __builtin_popcountll(bit) << '\n';
        for (int i = 0; i < n; i++) {
            if (get_bit(bit, i)) cout << a[i] << ' ';
        }
        cout << '\n';
        cout << __builtin_popcountll(bit2) << '\n';
        for (int i = 0; i < n; i++) {
            if (get_bit(bit2, i)) cout << a[i] << ' ';
        }
        cout << '\n';
    };

    auto backtrack = [&](int id, int psum, int sum, int bit, auto&& backtrack) -> void {
        psum &= msk;
        if (id == 0) {
            if (psum) {
                sum += a[0];
                bit |= 1;
            }
            if (mp[sum]) {
                print_ans(mp[sum], bit);
                exit(0);
            }
            mp[sum] = bit;
            return;
        }
        
        if (dp[id][psum] == dp[id-1][psum]) {
            backtrack(id - 1, psum, sum, bit, backtrack);
        } else {
            backtrack(id - 1, psum - a[id], sum + a[id], bit | (1LL<<id), backtrack);
            backtrack(id - 1, psum, sum, bit, backtrack);
        }
    };
    backtrack(n - 1, mx_sum, 0, 0, backtrack);
    cout << "IMPOSSIBLE\n";
}
 
signed main() {
	IO;	
	solve();	
}
