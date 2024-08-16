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

pii exgcd(int a, int b) {
	if(b == 0) return {1 ,0};
	pii ans = exgcd(b, a % b);
	return {ans.S, ans.F - a / b * ans.S};
}

pii mexgcd(int a, int b) {
    pii res = exgcd(a, b);
    int g = gcd(a, b);
    int b1 = b / g;
    res.X = (res.X % b1 + b1) % b1;
    res.Y = (g - a * res.X) / b;
    return res;
}

inline void solve() {
    int n, a, b, c, x;
    cin >> n >> a >> b >> c >> x;
    pair<__int128, __int128> pq = exgcd(b, c);
    int g = gcd(b, c);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        __int128 X = x - a * i;
        if (X < 0) break;
        if (X % g) continue; 
        __int128 p = X / g * pq.F, q = X / g * pq.S;

        __int128 c1 = c / g;
        __int128 b1 = b / g;
        p = (p % c1 + c1) % c1;
        if (!p) p += c1;
        q = (X - b * p) / c;

        if (q > n) {
            q = q - ((q - n - 1) / b1 + 1) * b1;
            p = (X - c * q) / b;
        }

        if (q <= 0 || q > n || p <= 0 || p > n) continue;

        ans += min((n - p) / c1, (q - 1) / b1) + 1;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
