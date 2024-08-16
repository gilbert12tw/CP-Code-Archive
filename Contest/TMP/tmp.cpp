#include<bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int n, sum[2001][2001], mx[2001][2001];
char mp[2001][2001];
pii st, ed;

int check(int x, int y) {
    return (x <= n && x > 0 && y <= n && y > 0);
}

int get_sum(int ux, int uy, int bx, int by) {
    if (!check(ux, uy) || !check(bx, by)) return -1;
    return sum[ux][uy] - sum[bx-1][uy] - sum[ux][by-1] + sum[bx-1][by-1];
}

int vis[2001][2001];
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
void bfs(int x, int y, int thres) {
    queue<pii> q;
    vis[x][y] = 1;
    q.push(make_pair(x, y));
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        x = cur.first; y = cur.second;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (check(nx, ny) && !vis[nx][ny] && mx[nx][ny] >= thres) {
                vis[nx][ny] = 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
}

int sol(int thres) {
    memset(vis, 0, sizeof vis);
    bfs(st.first, st.second, thres);
    return vis[ed.first][ed.second];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (mp[i] + 1);
        for (int j = 1; j <= n; j++) {
            if (mp[i][j] == 'S') 
                st = make_pair(i, j);
            if (mp[i][j] == 'E') 
                ed = make_pair(i, j);
            if (mp[i][j] == '#') 
                sum[i][j] = 1;
            sum[i][j] += sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1];
        }
    }
    assert(1 <= n && n <= 2000);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (mp[i][j] == '#') continue;
            int res = 1;
            for (int k = 11; k >= 1; k--) {
                int tmp = res | (1<<k);
                int r = (tmp - 1) / 2;
                if (get_sum(i + r, j + r, i - r, j - r) == 0) {
                    res = tmp;
                }
            }
            mx[i][j] = res;
        }
    }    

    if (!sol(1)) {
        cout << -1 << '\n';
        return 0;
    }

    int ans = 1;
    for (int k = 11; k >= 1; k--) {
        int tmp = ans | (1<<k);
        if (sol(tmp)) 
            ans = tmp;
    }
    cout << ans << '\n';
}
