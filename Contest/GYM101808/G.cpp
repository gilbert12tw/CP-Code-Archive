#include<bits/stdc++.h>
//#define loli
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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }


__int128 mgcd(__int128 a, __int128 b) {
    int r;
    while (a && b) {
        r = a % b;
        a = b; b = r;
    }
    return a | b;
}

__int128 lcm(__int128 x, __int128 y) {
    return (x * y) / mgcd(x, y);
}


inline void solve() {
    int n, X, Y;
    cin >> n >> X >> Y;
    if (Y % X != 0 || (n == 1 && X != Y)) {
        cout << -1 << '\n';
        return;
    }
    vector<int> a(n);
    int cnt = 0;
    for (int &i : a) {
        cin >> i;
        if (i % X != 0 || Y % i != 0)
            cnt++;
    }

    if (n == 1) {
        cout << (a[0] != X) << '\n';
        return;
    }

    if (cnt >= 2) {
        cout << cnt << '\n';
        return;
    }

    vector<int> factor;
    map<int, int> mp;
    int ty = Y;
    for (int i = 2; ty != 1; i++) {
        if (i * i > ty) {
            factor.eb(ty);
            mp[ty]++;
            break;
        }
        if (ty % i == 0) factor.eb(i);
        while (ty % i == 0) {
            ty /= i;
            mp[i]++;
        }
    }

    vector<__int128> pre_gcd(n), pre_lcm(n), suf_gcd(n), suf_lcm(n);
    pre_gcd[0] = pre_lcm[0] = a[0];
    suf_gcd[n-1] = suf_lcm[n-1] = a[n-1];
    for (int i = 1; i < n; i++) {
        pre_gcd[i] = mgcd(pre_gcd[i-1], (__int128)a[i]);
        pre_lcm[i] = lcm(pre_lcm[i-1], (__int128)a[i]);
    }
    for (int i = n - 2; i >= 0; i--) {
        suf_gcd[i] = mgcd(suf_gcd[i+1], (__int128)a[i]);
        suf_lcm[i] = lcm(suf_lcm[i+1], (__int128)a[i]);
    }

    if (cnt == 0 && suf_gcd[0] == X && suf_lcm[0] == Y) {
        cout << 0 << '\n';
        return;
    }
    int out_0 = suf_gcd[0], out_1 = suf_lcm[0];
    test(out_0, out_1);

    int ok = 0;
    for (int i = 0; i < n; i++) {
        __int128 gg, lm;
        if (i == 0) {
            gg = suf_gcd[1];
            lm = suf_lcm[1];
        } else if (i == n - 1) {
            gg = pre_gcd[n-2];
            lm = pre_lcm[n-2];
        } else {
            gg = mgcd(pre_gcd[i-1], suf_gcd[i+1]);
            lm = lcm(pre_lcm[i-1], suf_lcm[i+1]);
        }

        if (gg % X || Y % lm) continue;
        //test(ban, lm, gg);

        __int128 tmp_a = X;
        for (int fac : factor) {
            int cc = 0, cca = 0;
            __int128 tlm = lcm(tmp_a, lm);
            while (tlm % fac == 0) {
                tlm /= fac;
                cc++;
            }
            __int128 tta = tmp_a;
            while (tta % fac == 0) {
                tta /= fac;
                cca++;
            }
            if (cc < mp[fac]) {
                for (int kk = 0; kk < mp[fac] - cca; kk++)
                    tmp_a *= fac;
            }
        }

        //test(tmp_a);
        if (mgcd(gg, tmp_a) == X && lcm(lm, tmp_a) == Y) {
            ok = 1;
            break;
        }
    }
    if (ok) cout << 1 << '\n';
    else cout << 2 << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
