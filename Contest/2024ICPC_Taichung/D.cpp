#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef long long ll;
typedef pair<ll, ll> pll;

const ll INF = (1LL<<60);

vector<vector<char> > grid;
vector<vector<vector<vector<ll> > > > dis;
ll n, m;
pll st, ed;

pll step[4] = {
    mp(1, 0),
    mp(-1, 0),
    mp(0, 1),
    mp(0, -1)
};

pll operator + (pll A, pll B) {
    return mp(A.fi + B.fi, A.se + B.se);
}

int main () {
    cin >> n >> m;
    grid.resize(n);
    for (ll i = 0;i < n; ++i) {
        grid[i].resize(m);
        for (ll j = 0;j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                st = mp(i, j);
            }
            if (grid[i][j] == 'T') {
                ed = mp(i, j);
            }
        }
    }
    dis.resize(n);
    for (ll i = 0;i < n; ++i) {
        dis[i].resize(m);
    }
    for (ll i = 0;i < n; ++i) {
        for (ll j = 0;j < m; ++j) {
            dis[i][j].resize(4);
            for (ll k = 0;k < 4; ++k) {
                dis[i][j][k].resize(4);
                for (auto& val : dis[i][j][k]) {
                    val = -1;
                }
            }
        }
    }
    auto invalid = [&](pll pos) -> bool {
        if (pos.fi < 0 || pos.fi >= n || pos.se < 0 || pos.se >= m) return true;
        if (grid[pos.fi][pos.se] == '#') return true;
        return false;
    };
    dis[st.fi][st.se][0][0] = 0;
    queue<pair<pll, pll> > que;
    que.push(mp(st, mp(0, 0)));
    while (!que.empty()) {
        pll now = que.front().fi;
        ll dir = que.front().se.fi;
        ll con = que.front().se.se;
        //cout << now.fi << " " << now.se << " " << dir << " " << con << " " << dis[now.fi][now.se][dir][con] << "\n";
        que.pop();
        for (ll d = 0;d < 4; ++d) {
            pll nxt_now = now + step[d];
            ll nxt_dir = d;
            ll nxt_con = 0;
            if (dir == d) {
                nxt_con = con+1;
            } else {
                nxt_con = 1;
            }
            if (nxt_con >= 4 || invalid(nxt_now) || dis[nxt_now.fi][nxt_now.se][nxt_dir][nxt_con] != -1) {
                continue;
            }
            dis[nxt_now.fi][nxt_now.se][nxt_dir][nxt_con] = dis[now.fi][now.se][dir][con] + 1;
            que.push(mp(nxt_now, mp(nxt_dir, nxt_con)));
        }
    }
    ll ans = INF;
    for (ll d = 0; d < 4; ++d) {
        for (ll con = 1; con < 4; ++con) {
            ll val = dis[ed.fi][ed.se][d][con];
            if (val != -1)
                ans = min(ans, val);
        }
    }
    cout << (ans == INF ? -1 : ans) << "\n";
    return 0;
}
