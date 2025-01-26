#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define F first
#define S second
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> seat(n, vector<int>(m));
    vector<vector<int>> goal(n, vector<int>(m));
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> seat[i][j];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> goal[i][j];

    vector<pair<pii, pii>> ans;
    auto swp = [&](int a, int b, int x, int y) {
        swap(seat[a][b], seat[x][y]);
        ans.eb(mkp(mkp(a+1, b+1), mkp(x+1, y+1)));
    };

    auto chg = [&](int a, int b, int x, int y) {
        int v1 = seat[a][b], v2 = seat[x][y];
        int ed = b;
        for (int i = b; i < m; i++) {
            if (seat[a][i] < v2) ed = i;
            else break;
        }
        for (int i = ed; i >= b; i--) {
            swp(a, i, x, y);
        }
    };

    int inf = n * m + 10;
    while (true) {
        int mn = inf, xx, yy;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (seat[i][j] != goal[i][j] && seat[i][j] < mn) {
                    mn = seat[i][j];
                    xx = i, yy = j;
                }
            }
        }
        if (mn == inf) break;
        int aa = -1, bb = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (seat[i][j] != goal[i][j] && goal[i][j] == mn) {
                    aa = i, bb = j;
                }
            }
        }
        chg(xx, yy, aa, bb);
    }

    cout << SZ(ans) << '\n';
    for (auto p : ans) cout << p.F.F << ' ' << p.F.S << ' ' << p.S.F << ' ' << p.S.S << '\n';
}

signed main() {
	IO;	
	solve();	
}
