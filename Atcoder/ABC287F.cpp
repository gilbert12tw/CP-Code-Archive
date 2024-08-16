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

const int mxN = 5005;

int n;
vector<int> g[mxN];
int dp[2][mxN][mxN], tmp[2][mxN], sz[mxN]; 
// dp[0][u][k] = # of subgraph [is root be choosen?][root at u][k cc]

void madd(int &a, int b) {
    b %= mod;
    a += b;
    if (a > mod) a -= mod;
}

void dfs(int u, int p) {
    sz[u] = 1;
    dp[1][u][1] = 1;
    dp[0][u][0] = 1;

    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u); 

        for (int i = 0; i <= sz[u]; i++) {
            for (int j = 0; j <= sz[v]; j++) {
                madd(tmp[0][i+j], dp[0][u][i] * (dp[0][v][j] + dp[1][v][j]));
                madd(tmp[1][i+j], dp[1][u][i] * dp[0][v][j]);
                if (i && j) madd(tmp[1][i+j-1], dp[1][u][i] * dp[1][v][j]);
            }
        }

        sz[u] += sz[v];

        for (int i = 0; i <= sz[u]; i++) {
            dp[0][u][i] = tmp[0][i];
            dp[1][u][i] = tmp[1][i];
            tmp[0][i] = tmp[1][i] = 0;
        }
    }
}

inline void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].eb(v); 
        g[v].eb(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i ++) 
        cout << (dp[0][1][i] + dp[1][1][i]) % mod << '\n';
}

signed main() {
    IO;	
    solve();	
}
