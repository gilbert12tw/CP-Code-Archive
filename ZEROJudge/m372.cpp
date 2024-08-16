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
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

vector<int> g[500 * 500 + 20];
bool dir[501][501][4];
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}; // D, R, U, L
int n, m;
int vis[501 * 501];

int id(int x, int y) {
    return x * m + y;
}

int cnt = 0;
void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    cnt++;
    for (int v : g[u]) 
        dfs(v);
}

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            switch (c) {
                case 'X':
                    dir[i][j][0] = 1;
                    dir[i][j][1] = 1;
                    dir[i][j][2] = 1;
                    dir[i][j][3] = 1;
                    break;
                case 'I':
                    dir[i][j][0] = 1;
                    dir[i][j][1] = 0;
                    dir[i][j][2] = 1;
                    dir[i][j][3] = 0;
                    break;
                case 'H':
                    dir[i][j][0] = 0;
                    dir[i][j][1] = 1;
                    dir[i][j][2] = 0;
                    dir[i][j][3] = 1;
                    break;
                case 'L':
                    dir[i][j][0] = 0;
                    dir[i][j][1] = 1;
                    dir[i][j][2] = 1;
                    dir[i][j][3] = 0;
                    break;
                case '7':
                    dir[i][j][0] = 1;
                    dir[i][j][1] = 0;
                    dir[i][j][2] = 0;
                    dir[i][j][3] = 1;
                    break;
                case 'F':
                    dir[i][j][0] = 1;
                    dir[i][j][1] = 1;
                    dir[i][j][2] = 0;
                    dir[i][j][3] = 0;
                    break;
                case 'J':
                    dir[i][j][0] = 0;
                    dir[i][j][1] = 0;
                    dir[i][j][2] = 1;
                    dir[i][j][3] = 1;
                    break;
                default:
                    dir[i][j][0] = 0;
                    dir[i][j][1] = 0;
                    dir[i][j][2] = 0;
                    dir[i][j][3] = 0;
                    break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
           for (int d = 0; d < 2; d++) {
               if (!dir[i][j][d]) continue;
               int x = i + dx[d], y = j + dy[d];
               if (x < n && y < m && dir[x][y][d+2]) {
                   g[id(i, j)].eb(id(x, y));
                   g[id(x, y)].eb(id(i, j));
               }
           }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) 
        if (SZ(g[id(i, j)]) > 0 && !vis[id(i, j)]) { 
            cnt = 0;
            dfs(id(i, j));
            ans = max(ans, cnt);
        }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
