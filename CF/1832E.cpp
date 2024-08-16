#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
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

const int mxN = 1e7 + 5;

const int J[10] = {1, 1, 2, 6, 24, 120};
int n, a1, x, y, m, k;

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

int a[mxN], c[mxN], sumc[mxN];
void build() {
    a[1] = a1;
    for (int i = 2; i <= n; i++) {
        a[i] = (a[i-1] * x + y) % m; 
        test(i, a[i]);
    }
    int di = inv(J[k]); 
    for (int i = 1; i <= n; i++) {
        if (i < k) continue;
        c[i] = 1;
        for (int j = 0; j < k; j++) {
            c[i] = c[i] * (i - j) % mod; 
        }
        c[i] = c[i] * di % mod;
        sumc[i] = (sumc[i-1] + c[i]) % mod;
    }
}

int get_b(int n) {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = (res + a[i] * sumc[n-i+1] % mod) % mod;
    }
    return res;
}

inline void solve() {
    cin >> n >> a1 >> x >> y >> m >> k;
    build();
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int b = get_b(i) - get_b(i-1);
        test(i, b);
        ans = ans ^ (b * i);
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
