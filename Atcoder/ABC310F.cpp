#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<bitset>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
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
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

int n;
int a[101];
int dp[101][(1<<11)+1];

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

void madd(int &a, int b) {
    a += b;
    if (a >= mod) a %= mod;
}

inline void solve() {
    cin >> n;
    int div = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        div = (div * a[i]) % mod;
    }

    dp[0][1] = 1;
    int msk = (1<<11) - 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 11 && j <= a[i]; j++) {
            for (int k = 1; k < (1<<11); k++) {
                if (j <= 10) { 
                    madd(dp[i][msk&((k<<j)|k)], dp[i-1][k]);
                }
                else {
                    madd(dp[i][k], (dp[i-1][k] * (a[i]-10)) % mod);
                }
            }
        }

        /*
        int tmp = 0;
        for (int j = 1; j < (1<<11); j++) {
            if (get_bit(j, 0)) 
                tmp += dp[i][j];
        }
        */
    }

    int ans = 0;
    for (int i = 0; i < (1<<11); i++) {
        if (get_bit(i, 10))
            madd(ans, dp[n][i]);
    }
    cout << (ans * inv(div)) % mod;
}

signed main() {
	IO;	
	solve();	
}
