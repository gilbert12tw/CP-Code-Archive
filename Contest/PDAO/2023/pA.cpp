#include<bits/stdc++.h>
#define loli
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
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

const int mxN = 2e6 + 5;

int d[mxN], J[mxN];

int np[10000001];
vector<int> prime;

void sieve(int n) {
	for(int i = 2; i <= n; i++) {
		if(np[i] == 0) np[i] = i, prime.eb(i);
		for(int j : prime) {
			if(i * j > n) break;
			np[i * j] = j;
			if(np[i] == j) break;
		}
	}
}

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

inline void solve() {
    int ans = 0;
    int n; cin >> n;
    J[0] = 1;
    for (int i = 1; i <= n; i++) J[i] = J[i-1] * prime[i-1] % mod;

    vector<int> v;
    for (int i = 1; i < n; i++) {
        ans -= d[i];
        for (int j = i + i; j <= n; j += i) {
            ans++;
            d[j]++;
        }
        v.eb(ans % mod);
    } 

    reverse(ALL(v));
    v.eb(0);

    for (int i = 0; i < n; i++) {
        //cout << (v[i] * inv(J[i+1]) % mod) << ' ';
        test(i+1, v[i]);
    }
}

signed main() {
	IO;	
    sieve(10000000);
	solve();	
}
