#include<bits/stdc++.h>
#define loli
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

const int mxN = 1e6 + 5;
int n, J[mxN], invJ[mxN];
inline int fp(int a, int b, int p) {
    int res = 1;
    while(b) {
        if(b&1) res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
 
inline int inv(int x) {return fp(x, mod - 2, mod);}
 
void build(int n) {
    J[1] = J[0] = invJ[1] = invJ[0] = 1;
    for(int i = 2; i <= n; i++) J[i] = J[i - 1] * i % mod;
    invJ[n] = fp(J[n], mod - 2, mod);
    for(int i = n - 1; i >= 2; i--) invJ[i] = invJ[i + 1] * (i + 1) % mod;
}
 
int C(int n, int m) {
	if (n < m) return 0;
    if(n == m or m == 0) return 1;
    int res = J[n] * invJ[n - m] % mod * invJ[m] % mod;
    return res;
}

inline void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n), suma(n), sumb(n);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            suma[i] = a[i];
            sumb[i] = b[i];
        } else {
            suma[i] = suma[i-1] + a[i];
            sumb[i] = sumb[i-1] + b[i];
        }
    }

    vector<int> Csum(sumb[n-1] + 1);
    Csum[0] = 1;
    int totSilver = sumb[n-1], totGold = suma[n-1];
    for (int i = 1; i < SZ(Csum); i++) {
        Csum[i] = (Csum[i-1] + C(totSilver, i)) % mod;
    }

    int S = inv(fp(2, totSilver, mod));
    while (q--) {
        int l, r; cin >> l >> r;
        l -= 2; r--;
        int silver = sumb[r] - (l < 0 ? 0 : sumb[l]);
        int gold = suma[r] - (l < 0 ? 0 : suma[l]);
        int dif = (gold - (totGold - gold)) - (totSilver - silver);
        //test((gold - (totGold - gold)), (totSilver - silver));

        int x = -dif + 1;
        //test(dif, x);
        if (x > totSilver) {
            cout << 0 << ' ';
        } else {
            int res = (Csum[totSilver] - (x - 1 < 0 ? 0 : Csum[x - 1]) + mod) % mod;
            cout << (res * S) % mod << ' ';
        }
    }
}

signed main() {
	IO;	
    build(1000000);
    solve();
}
