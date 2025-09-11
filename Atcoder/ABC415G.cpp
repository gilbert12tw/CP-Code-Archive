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
    ll n;
    int m;
    cin >> n >> m;

    if (m == 0) {
        cout << n << endl;
        return;
    }

    vector<int> a(m), b(m), c(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i];
        c[i] = a[i] - b[i];
    }

    ll total_drinks = n;
    ll empty_bottles = n;

    int best_idx = -1;
    for (int i = 0; i < m; ++i) {
        if (best_idx == -1 || (ll)b[i] * c[best_idx] > (ll)b[best_idx] * c[i]) {
            best_idx = i;
        }
    }
    
    const int A_MAX = 300;
    const int C_MAX = 300;
    const int DP_THRESHOLD = 90000;

    if (best_idx != -1 && empty_bottles > DP_THRESHOLD) {
        ll best_c = c[best_idx];
        ll best_b = b[best_idx];
        ll k = (empty_bottles - DP_THRESHOLD) / best_c;
        total_drinks += k * best_b;
        empty_bottles -= k * best_c;
    }

    vector<vector<int>> best_B_for_C_A(C_MAX + 1, vector<int>(A_MAX + 1, -1));
    for (int i = 0; i < m; ++i) {
        ckmax(best_B_for_C_A[c[i]][a[i]], b[i]);
    }

    for (int cur_c = 1; cur_c <= C_MAX; ++cur_c) {
        for (int cur_a = 1; cur_a <= A_MAX; ++cur_a) {
            ckmax(best_B_for_C_A[cur_c][cur_a], best_B_for_C_A[cur_c][cur_a - 1]);
        }
    }
    
    int dp_limit = empty_bottles;
    vector<ll> dp(dp_limit + 1, 0);

    for (int e = 1; e <= dp_limit; ++e) {
        for (int cur_c = 1; cur_c <= C_MAX; ++cur_c) {
            if (e >= cur_c) {
                int affordable_a = min(e, A_MAX);
                int b_val = best_B_for_C_A[cur_c][affordable_a];
                if (b_val != -1) {
                    ckmax(dp[e], dp[e - cur_c] + b_val);
                }
            }
        }
    }
    
    if (dp_limit > 0) {
        total_drinks += dp[dp_limit];
    }
    cout << total_drinks << endl;
}

signed main() {
	IO;	
	solve();	
}
