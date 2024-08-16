#include<bits/stdc++.h>
#define pii pair<int, int>
#define mkp make_pair
using namespace std;

#define id(x, a) (x * 11 + a)

int mat[220][220][11];


int spfa(int n, int s, int t, int lim) {
    queue<pii> q;
    vector<int> dis((n + 1) * 12, -1), in((n + 1) * 12, 0);

    for (int i = 0; i <= 10; i++) {
        dis[id(s, i)] = 0;
        q.push(mkp(s, i));
        in[id(s, i)] = 1;
    }

    while (!q.empty()) {
        int u = q.front().first;
        int last_flight = q.front().second;
        q.pop();
        int now_id = id(u, last_flight);
        in[now_id] = 0;

        for (int v = 0; v <= n; v++) {
            for (int f = 0; f <= 10; f++) {
                if (mat[u][v][f] == -1) continue;
                int w = mat[u][v][f];
                if (f != last_flight) w += 5;
                if (dis[id(v, f)] == -1 || dis[id(v, f)] > dis[now_id] + w) {
                    dis[id(v, f)] = dis[now_id] + w;
                    if (!in[id(v, f)]) {
                        in[id(v, f)] = 1;
                        q.push(mkp(v, f));
                    }
                }
            }
        }
    }

    int res = -1;
    for (int i = 0; i <= 10; i++) 
        if (dis[id(t, i)] != -1) {
            if (res == -1 || dis[id(t, i)] < res)
                res = dis[id(t, i)];
        }
    if (res > lim) return -1;
    return res;
}

inline void solve() {
    int n, q;
    cin >> n >> q;
    memset(mat, -1, sizeof mat);
    while (q--) {
        string s; cin >> s;
        int u, v, p, a;
        if (s[0] == 'A') {
            cin >> u >> v >> p >> a;
            assert(a <= 10);
            if (mat[u][v][a] == -1 || mat[u][v][a] > p) 
                mat[u][v][a] = p;
        } else if (s[0] == 'D') {
            cin >> u >> v >> a;
            assert(a <= 10);
            mat[u][v][a] = -1;
        } else {
            cin >> u >> v >> p;
            cout << spfa(n, u, v, p) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}
