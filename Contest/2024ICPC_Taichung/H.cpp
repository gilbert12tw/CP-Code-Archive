#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<ll, ll> pll;

const ll INF = (1LL<<60);
const ll MOD = 998244353;
const ll N = 1e6 + 5;

ll dp[N][3];
ll pre[N][2];
ll fac[N], rfac[N];
ll n, k;

ll POW(ll base, ll ti) {
    ll ret = 1;
    for (ll i = 60;i >= 0; --i) {
        ret = ret * ret % MOD;
        if ((ti>>i)&1)
            ret = ret * base % MOD;
    }
    return ret;
}

ll C(ll _n, ll _m) {
    if (_m > _n) return 0;
    return fac[_n]*rfac[_n-_m]%MOD*rfac[_m] % MOD;
}


int main() {
    fac[0] = fac[1] = 1;
    for (ll i = 1;i < N; ++i) {
        fac[i] = i * fac[i-1] % MOD;
    }
    rfac[0] = 1;
    for (ll i = 1;i < N; ++i) {
        rfac[i] = POW(fac[i], MOD-2);
    }
    cin >> n >> k;
    --n;
    if (k == 1) {
        cout << "1\n";
        return 0;
    }
    dp[0][0] = dp[0][1] = 1;
    dp[1][0] = dp[1][1] = 1;
    pre[0][0] = pre[0][1] = 1;
    pre[1][0] = pre[1][1] = 2;
    for (ll i = 2;i <= n; ++i) {
        ll j = max(-1LL, i-k);
        dp[i][0] = (pre[i-1][0] - (j == -1 ? 0 : pre[j][0]) + MOD) % MOD;
        dp[i][1] = (pre[i-1][1] - (j == -1 ? 0 : pre[j][1]) + MOD) % MOD;
        pre[i][0] = (pre[i-1][0] + dp[i][1]) % MOD;
        pre[i][1] = (pre[i-1][1] + dp[i][0]) % MOD;
    }
    //for (ll i = 1;i <= n; ++i) {
    //    cout << dp[i][0] << " " << dp[i][1] << "\n";
    //}
    ll ans = 1;
    for (ll i = 0;i < n; ++i) {
        ans = (ans + C(n, i) * (dp[n-i][0] + dp[n-i][1]) % MOD) % MOD;
    }
    cout << ans << "\n";
    return 0;
}
