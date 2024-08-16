#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
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
#define mod 1000000007
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

const int mxN = 24;

int n, k;
int a[mxN+5], sum[(1<<mxN)+5], dp[(1<<mxN)+5];
int lb[40];

#define lowbit(x) (x&-x)
inline void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) lb[(1<<i)%37] = i;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 1; i < (1<<n); i++) {
        sum[i] = sum[i ^ lowbit(i)] + a[lb[lowbit(i)%37]];
    }
    cin >> k;
    vector<int> v(k);
    for (int &i : v) cin >> i;

    dp[0] = 1;
    for (int i = 0; i < (1<<n); i++) {
        int ok = 1;
        for (int j : v) if (sum[i] == j) 
            ok = 0;
        if (!ok) {
            dp[i] = 0;
            continue;
        }
        for (int j = 0; j < n; j++) {
            if (get_bit(i, j) == 0) {
                dp[i|(1<<j)] = (dp[i|(1<<j)] + dp[i]);
                if (dp[i|(1<<j)] >= mod) dp[i|(1<<j)] -= mod;
            }
        }
    }
    cout << dp[(1<<n)-1] << '\n';
}

signed main() {
	IO;	
	solve();	
}
