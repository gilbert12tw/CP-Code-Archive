#include<bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
//#pragma GCC optimize("unroll-loops,no-stack-protector,Ofast")
using namespace std;
//using namespace __gnu_pbds;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ld;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define pb push_back 
#define mp make_pair
#define fi first
#define se second
#define lwb lower_bound
#define setp setprecision
#define SZ(_a) (ll)(_a).size()
#define SQ(_a) ((_a)*(_a))
#define all(_a) (_a).begin(), (_a).end()
#define chmax(_a, _b) _a = max(_a, _b)
#define chmin(_a, _b) _a = min(_a, _b)
template <class T> inline ostream& operator << (ostream& out, vector<T> v) {
    for (int i = 0;i < SZ(v); ++i) out << v[i] << (i == SZ(v)-1 ? "" : " ");
    return out;
}

template <class A, class B> inline ostream& operator << (ostream& out, pair<A, B> p) {
    out << "(" << p.fi << ", " << p.se << ")";
    return out;
}

template <class A, class B> inline pair<A, B> operator + (pair<A, B> pA, pair<A, B> pB) {
    return make_pair(pA.fi+pB.fi, pA.se+pB.se);
}

template <class A, class B> inline pair<A, B> operator - (pair<A, B> pA, pair<A, B> pB) {
    return make_pair(pA.fi-pB.fi, pA.se-pB.se);
}

template <class A, class B, class C> inline pair<A, B> operator * (pair<A, B> pA, C pB) {
    return make_pair(pA.fi*pB, pA.se*pB);
}



const ll N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ld pi = acos(-1);
const ll INF = (1LL<<60);

bool g(string a, string b) {
    if (SZ(a) != SZ(b)) return (SZ(a) > SZ(b));
    for (int i = 0;i < SZ(a); ++i) {
        if (a[i] != b[i]) return (a[i] > b[i]);
    }
    return false;
}


bool ge(string a, string b) {
    if (SZ(a) != SZ(b)) return (SZ(a) > SZ(b));
    for (int i = 0;i < SZ(a); ++i) {
        if (a[i] != b[i]) return (a[i] > b[i]);
    }
    return true;
}

ll dp[N][21];
string s, limit;

void solve() {
    for (ll i = 0;i < N; ++i)
        for (ll j = 0;j < 21; ++j)
            dp[i][j] = INF;
    cin >> s >> limit;
    for (ll i = 0;i < SZ(s); ++i) {
        for (ll j = 1;j <= SZ(limit) && i-j >= -1; ++j) {
            if (i-j == -1) dp[i][j] = 0;
            string ta = s.substr(i-j+1, j);
            if (g(ta, limit)) break;
            for (ll k = 1;k <= SZ(limit) && i-j-k >= -1; ++k) {
                string tb = s.substr(i-j-k+1, k);
                if (g(tb, limit)) break;
                if (ge(ta, tb)) 
                    dp[i][j] = min(dp[i][j], dp[i-j][k]+1);
            }
        }
    }
    ll ans = INF;
    for (ll j = 0;j <= SZ(limit); ++j)
        ans = min(ans, dp[SZ(s)-1][j]);
    if (ans == INF) {
        cout << "NO WAY\n";
    } else {
        cout << ans << "\n";
    }
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);
    solve();
    return 0;
}

/* Don't forget to check:
 * special case (n=1?)
 * array bounds.
 * hash collision
 * MOD in every step
*/
