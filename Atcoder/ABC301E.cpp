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

const int mxN = 2e6 + 5;

int n, m, t;
char mat[301][301];
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int go[25][25];

int bfs(pii s, pii g) {
    vector<vector<int>> dis(n, vector<int>(m, inf));
    dis[s.X][s.Y] = 0;
    queue<pii> q;
    q.push(s);
    while (!q.empty()) {
        pii u = q.front(); q.pop();
        int d = dis[u.X][u.Y];
        if (u == g) return d;
        for (int dr = 0; dr < 4; dr++) {
            int nx = u.X + dx[dr], ny = u.Y + dy[dr];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && mat[nx][ny] != '#' && dis[nx][ny] > d + 1) {
                dis[nx][ny] = d + 1;
                q.push(mkp(nx, ny));
            }
        }
    }
    return inf;
}

inline void solve() {   
    cin >> n >> m >> t;
    vector<pii> v;
    pii S, G;
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 'o') v.eb(i, j);
            else if (mat[i][j] == 'S') S = mkp(i, j);
            else if (mat[i][j] == 'G') G = mkp(i, j);
        }
    }

    v.eb(S);
    reverse(ALL(v));
    v.eb(G);

    for (int i = 0; i < SZ(v); i++) {
        for (int j = 0; j < SZ(v); j++) {
            if (i == j) go[i][j] = 0;
            else go[i][j] = bfs(v[i], v[j]);
        }
    }

    int V = SZ(v);
    vector<vector<int>> dp(V, vector<int>((1<<V) + 1, inf));
    dp[0][1] = 0;
    for (int i = 1; i < (1<<V); i++) {
        for (int j = 0; j < V; j++) {
            if (get_bit(i, j) == 0) continue;
            for (int k = 0; k < V; k++) {
                if (j == k || get_bit(i, k)) continue;
                dp[k][i^(1<<k)] = min(dp[k][i^(1<<k)], dp[j][i] + go[j][k]);
            }
        }
    }

    int ans = -1;
    for (int i = 0; i < (1<<V); i++) {
        if (get_bit(i, 0) && get_bit(i, (V-1)) && dp[V-1][i] <= t) {
            int bcnt = __builtin_popcount(i) - 2;
            ans = max(ans, bcnt); 
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
