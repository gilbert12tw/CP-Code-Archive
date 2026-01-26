#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define eb emplace_back
#define ALL(a) a.begin(), a.end()
#define SZ(a) ((int)a.size())

#ifdef debug
template <typename T>
ostream& operator << (ostream &o, vector<T> vec) {
    o << "{"; int f = 0; for (T i : vec) o << (f++ ? " " : "") << i; return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m"; (..., (cerr << a << " ")); cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#endif

const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> mat(n);

    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }

    #define ok(x, y) (x >= 0 && x < n && y >= 0 && y < m)
    auto check = [&](int x, int y) -> int {
        int res = 0;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (ok(nx, ny) && mat[nx][ny] == '#')
                res++;
        }
        return res;
    };

    vector<pii> que;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == '.' && check(i, j) == 1) {
                que.eb(i, j);
            }
        }
    }

    while (!que.empty()) {
        for (auto [x, y] : que) {
            mat[x][y] = '#';
        }
        vector<pii> nxt;
        for (auto [x, y] : que) {
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (ok(nx, ny) && mat[nx][ny] == '.' && check(nx, ny) == 1) {
                    nxt.eb(nx, ny);
                }
            }
        }
        que = move(nxt);
    }

    int res = 0;
    for (int i = 0; i < n; i++) res += count(ALL(mat[i]), '#');
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
