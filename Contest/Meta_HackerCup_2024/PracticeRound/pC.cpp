#include<bits/stdc++.h>
#include"jngen.h"
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
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)

inline pii sub(const pii &a, const pii &b) {
    return mkp(a.X - b.X, a.Y - b.Y);
}

inline int cross(const pii &a, const pii &b) {
    return a.X * b.Y - a.Y * b.X;
}

inline void solve(int cs) {
    int n; cin >> n;
    vector<pii> pt(n);
    for (auto &p : pt) cin >> p.X >> p.Y;
    
    int run_tm = min(200000LL, 10000000000 / n);

    int ans = 0;
    while (run_tm--) {
        int i = rnd.next(n);
        int j = rnd.next(n);
        if (i == j) j = (j + 1) % n;
        pii line_vec = sub(pt[i], pt[j]);
        pii ori = pt[i];

        int res = 0;
        #pragma omp parallel for private(i) reduction(+:res)
        for (int i = 0; i < n; i++) {
            pii p = pt[i];
            if (cross(line_vec, sub(pt[i], ori)) == 0) res++;
        }
        ans = max(ans, res);
    }

    cout << "Case #" << cs+1 << ": " << n - ans << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	for (int c = 0; c < T; c++) solve(c);	
}
