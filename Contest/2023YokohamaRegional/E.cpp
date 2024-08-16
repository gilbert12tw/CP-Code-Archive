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

inline void madd(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> dp((1<<n) + 5, 0);
    vector<vector<pii>> cons(n, vector<pii>());
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--; c--;
        cons[b].eb(a, c);
    }

    // dp
    dp[0] = 1;
    for (int i = 0; i < (1<<n); i++) {
        for (int j = 0; j < n; j++) {
            if (get_bit(i, j) == 0) {
                // add j
                int ok = 1;
                for (auto [a, b] : cons[j]) {
                    int cnt = get_bit(i, a) + get_bit(i, b);
                    if (cnt != 1) {
                        ok = 0;
                        //break;
                    }
                }
                if (ok) madd(dp[i | (1<<j)], dp[i]);
            }
        }
    }
    cout << dp[(1<<n)-1] << '\n';
}

signed main() {
	IO;	
	solve();	
}
