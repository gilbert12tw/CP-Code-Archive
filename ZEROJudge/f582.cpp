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

int n, m;
string s[1001];
vector<int> tr[1001];
int dp[1001][4];
map<char, int> mp = {{'A', 0}, {'U', 1}, {'C', 2}, {'G', 3}};

void dfs(int u, int pos) {
    if (SZ(tr[u]) == 0) {
        if (s[u][pos] == '@') {
            for (int i = 0; i < 4; i++) 
                dp[u][i] = 0;
        } 
        dp[u][mp[s[u][pos]]] = 0;
        return;
    }

    for (int v : tr[u]) {
        dfs(v, pos);
    }

    int cur_id = mp[s[u][pos]];
    if (s[u][pos] == '@') {
        for (int c = 0; c < 4; c++) {
            int res = 0;
            for (int v : tr[u]) {
                int mn = inf;
                for (int i = 0; i < 4; i++) {
                    mn = min(mn, dp[v][i] + (i != c));
                }
                res += mn;
            }
            dp[u][c] = res;
        }
    } else {
        int res = 0;
        for (int v : tr[u]) {
            int mn = inf;
            for (int i = 0; i < 4; i++) {
                mn = min(mn, dp[v][i] + (i != cur_id));
            }
            res += mn;
        }
        dp[u][cur_id] = res;
    }
}

inline void solve() {
    cin >> n >> m;
    int root = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cin >> s[x];
        if (x != y) tr[y].eb(x);
        else root = x;
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        memset(dp, 0x3f, sizeof dp);
        dfs(root, i);
        ans += min({dp[root][0], dp[root][1], dp[root][2], dp[root][3]});
    }
    cout << ans;
}

signed main() {
	IO;	
	solve();	
}
