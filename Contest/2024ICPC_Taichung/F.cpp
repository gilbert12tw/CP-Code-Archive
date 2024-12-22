#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<ll, ll> pll;

const ll INF = (1LL<<60);


#define llu unsigned long long
llu add(llu a, llu b, llu c) { return (__int128{a} + b) % c; }
llu mul(llu a, llu b, llu c) { return (__int128{a} * b % c) ; }

llu mpow(llu a, llu b, llu c) {
    llu res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, c);
        a = mul(a, a, c); b >>= 1;
    }
    return res;
}

unordered_map<llu, bool> dp;

inline bool isprime(llu x) {
    if (dp.find(x) != dp.end()) {
        return dp[x];
    }
    static auto witn = [](llu a, llu n, int t) {
        if (!a) return false;
        while (t--) {
            llu a2 = mul(a, a, n);
            if (a2 == 1 && a != 1 && a != n - 1) return true;
            a = a2;
        }
        return a != 1; 
    };
    if (x < 2) return dp[x] = false; 
    if (!(x & 1)) return dp[x] = (x == 2);
    int t = __builtin_ctzll(x - 1); llu odd = (x - 1) >> t;
    for (llu m : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
        if (witn(mpow(m % x, odd, x), x, t)) return dp[x] = false;
    return dp[x] = true;
}

ll shortest = (1LL<<60);
ll ans = 0;

void F(ll l, ll r) {
    bool flag = 0;
    //cout << l << " " << r << "\n";
    // LTR
    for (ll i = (l+r)/2; i >= (l+1); --i) {
        if (isprime(i)) {
            F(i, r);
            flag = 1;
            break;
        }
    }
    // RTL
    for (ll i = (l+r+1)/2;i < r; ++i) {
        if (isprime(i)) {
            F(l, i);
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        if (shortest == r-l) {
            ++ans;
        } else {
            if (r-l < shortest) {
                ans = 1;
                shortest = r-l;
            }
        }
    }
}

inline void solve() {
    ll l, r, L, R;
    ans = 0;
    shortest = (1LL<<60);
    cin >> l >> r;
    F(2*l, 2*r);
    cout << ans << "\n";
    //cout << isprime(2305843009213693951);
}

int main() {
    ll t;
    cin >> t;
    while (t--)
        solve();
}
