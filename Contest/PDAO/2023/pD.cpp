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

const int mxN = 400 + 5;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int w, l, m, o, t;
pii S;
int mat[mxN][mxN];
int dp[10001];

int check(int x, int y) {
    return 0 <= x && x < w && 0 <= y && y < l && mat[x][y] == 0;
}

int dis[mxN][mxN];
void BFS(pii s) {
    memset(dis, 0x3f, sizeof dis);
    dis[s.F][s.Y] = 0;
    queue<pii> q;
    q.push(s);
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (check(nx, ny) && dis[nx][ny] > dis[x][y] + 1) {
                dis[nx][ny] = dis[x][y] + 1;
                q.push(mkp(nx, ny));
            }
        }
    }
}

inline void solve() {
    cin >> w >> l >> S.F >> S.S >> m >> o >> t;
    for (int i = 0; i < o; i++) {
        int x, y; cin >> x >> y;
        mat[x][y] = 1;
    }

    BFS(S);

    for (int i = 0; i < t; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        int w = dis[x][y];
        for (int j = m; j >= w; j--) {
            dp[j] = max(dp[j], dp[j-w] + v);
        }
    }
    cout << dp[m] << '\n';

}

signed main() {
	IO;	
	solve();	
}
