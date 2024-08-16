#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,tune=native")
#pragma GCC optimize("no-stack-protector")
#define loli
using namespace std;
typedef long long ll;
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

const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
char mat[5000][5000];
int vis[5000][5000];
int n, m;

inline int check(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && mat[x][y] != '#' && vis[x][y] == 0);
}

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> mat[i];

    int q; cin >> q;
    vector<pii> que, nxtq;
    int ans = 0;
    for (int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        if (!vis[x][y]) {
            vis[x][y] = 1;
            que.eb(x, y);
        }
        while (!que.empty()) {
            auto [x, y] = que.back(); que.pop_back();
            ans++;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (check(nx, ny)) {
                    vis[nx][ny] = 1;
                    nxtq.eb(nx, ny);
                }
            }
        }
        swap(que, nxtq);
        cout << ans << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
