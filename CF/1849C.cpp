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

const int p1 = 131, p2 = 17;

inline void solve() {
    int n, m;
    string s;
    cin >> n >> m;
    cin >> s;
    s = "#" + s + "#";
    vector<int> sum(n + 1);
    vector<vector<int>> p(2, vector<int>(n + 1, 0)), hash, sump;
    hash = p;
    sump = p;
    set<pii> st;
    p[0][0] = p[1][0] = 1;

    for (int i = 1; i <= n; i++) {
        p[0][i] = p[0][i-1] * p1 % mod;
        p[1][i] = p[1][i-1] * p2 % mod;
        sump[0][i] = (sump[0][i-1] + p[0][i]) % mod;
        sump[1][i] = (sump[1][i-1] + p[1][i]) % mod;
    }

    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + (s[i] == '1');
        hash[0][i] = (hash[0][i-1] + (s[i] == '1') * p[0][i] % mod) % mod;
        hash[1][i] = (hash[1][i-1] + (s[i] == '1') * p[1][i] % mod) % mod;
    }

    test(hash[0][n], hash[1][n]);
    while (m--) {
        int l, r;
        cin >> l >> r;
        vector<int> ans(2);
        int one = sum[r] - sum[l-1];
        int zero = r - l + 1 - one;
        for (int i = 0; i < 2; i++) {
            ans[i] = (hash[i][n] - (hash[i][r] - hash[i][l-1]) % mod) % mod;
            if (ans[i] < 0) ans[i] += mod;
            int ll = l + zero, rr = r;
            ans[i] = (ans[i] + (sump[i][rr] - sump[i][ll-1]) % mod) % mod;
            if (ans[i] < 0) ans[i] += mod;
        }
        test(ans[0], ans[1]);
        st.insert(mkp(ans[0], ans[1]));
    }
   
    cout << SZ(st) << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
