#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<bitset>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
#define loli
using namespace std;
typedef long long ll;
#define int short
#define pii pair<int, int>
#define x first
#define y second
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

const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int n, m;
char mat[801][801];
int vis[801][801];
vector<pii> fire;
queue<pii> q[2], tmp;

inline bool ok(int x, int y) {
    return (x >= 0 && x < n && y >=0 && y < m && mat[x][y] != 'X'); 
}

inline bool caught(int x, int y, int step) {
    for (pii p : fire) {
        if (abs(x - p.x) + abs(y - p.y) <= 2 * step) return 1;
    }
    return 0;
}

inline bool bfs(int qid, int isBoy, int tms, int step) {
    tmp = q[qid];
    while (tms--) {
        while (!tmp.empty()) {
            pii now = tmp.front();
            tmp.pop();
            q[qid].pop();
            if (caught(now.x, now.y, step)) continue;
            for (int d = 0; d < 4; d++) {
                int nx = now.x + dx[d], ny = now.y + dy[d];
                if (ok(nx, ny) && !caught(nx, ny, step) && mat[nx][ny] != 'Z' && vis[nx][ny] != isBoy) {
                    if (vis[nx][ny] != -1) {
                        return true;
                    }
                    vis[nx][ny] = isBoy;
                    q[qid].push(mkp(nx, ny));
                }
            }
        }
        tmp = q[qid];
    }
    return false;
}

inline void solve() {
    scanf("%hd %hd", &n, &m);
    memset(vis, -1, sizeof vis);
    fire.clear();
    while (!q[0].empty()) q[0].pop();
    while (!q[1].empty()) q[1].pop();
    while (!tmp.empty()) tmp.pop();

    for (int i = 0; i < n; i++) {
        scanf("%s", mat[i]);
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 'M') 
                q[0].push(mkp(i, j));
            if (mat[i][j] == 'G')
                q[1].push(mkp(i, j));
            if (mat[i][j] == 'Z')
                fire.eb(mkp(i, j));
        }
    }

    // start BFS
    int step = 0;
    while (!q[0].empty() && !q[1].empty()) {
        step++;
        if (bfs(0, 1, 3, step) || bfs(1, 2, 1, step)) {
            printf("%hd\n", step);
            return;
        }
    }
    printf("-1\n");
}

signed main() {
    int T; scanf("%hd", &T);
    while (T--) {
        solve();	
    }
}
