#include<bits/stdc++.h>
#include<immintrin.h>
using namespace std;

typedef long long ll;
#define int ll
#define pii pair<int,int>
#define x first
#define y second
#define F first
#define S second
#define vi vector<int>
#define SZ(a) ((int)(a.size()))
#define ALL(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - (x).begin())
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) (((x)>>(y))&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);

template<class T> bool ckmin(T& a, const T& b) { return (b < a) ? (a = b, true) : false; }
template<class T> bool ckmax(T& a, const T& b) { return (a < b) ? (a = b, true) : false; }

const int mxN = 2e5 + 1;
static int prefix[mxN];
static int S[mxN];
static int dp_prev[mxN], dp_curr[mxN];
static int ans[mxN];
static int B[mxN];

inline void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) prefix[i] = prefix[i-1] + a[i];

    int m = n - k + 1;
    for (int i = 1; i <= m; i++) {
        S[i] = prefix[i + k - 1] - prefix[i - 1];
    }

    int max_intervals = n / k;


    const __m512i v_neg_inf = _mm512_set1_epi64(-INF);

    for (int j = 1; j <= max_intervals; j++) {
        dp_curr[0] = -INF;
        for (int i = 1; i < K; i++) {
            dp_curr[i] = dp_curr[i-1];
        }

        // Compute B[i] = (i>=K) ? dp_prev[i-K] + S[i] : -∞
        for (int i = 0; i <= m; i++) {
            if (i >= K) B[i] = dp_prev[i-K] + S[i];
            else B[i] = -1000000000000000000LL;
        }

        int blockSize = 64;
        for (int start = K; start <= m; start += blockSize) {
            int end = min(start + blockSize - 1, (int)m);
            int64_t curr_max = dp_curr[start-1];
            for (int idx = start; idx <= end; idx++) {
                int64_t candidate = B[idx];
                curr_max = (candidate > curr_max) ? candidate : curr_max;
                dp_curr[idx] = curr_max;
            }
        }

        ans[j] = dp_curr[m];

        // dp_prev = dp_curr
        {
            int i = 0;
            for (; i + 8 <= m+1; i += 8) {
                __m512i vcur = _mm512_loadu_si512((__m512i*)&dp_curr[i]);
                _mm512_storeu_si512((__m512i*)&dp_prev[i], vcur);
            }
            for (; i <= m; i++) {
                dp_prev[i] = dp_curr[i];
            }
        }
    }

    for (int i = 1; i <= max_intervals; i++) {
        cout << ans[i] << (i == max_intervals ? '\n' : ' ');
    }
}

signed main() {
    IO;
    solve();
    return 0;
}

