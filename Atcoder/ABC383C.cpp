#include<bits/stdc++.h>
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
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline void solve() {
    int n, m, d;
    cin >> n >> m >> d;
    vector<string> mat(n);
    vector<pii> pt;

    for (int i = 0; i < n; i++) {
        cin >> mat[i];
    }
    

    auto bfs = [&]() {
        vector<vector<int>> dis(n, vector<int>(m, -1));
        queue<pii> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 'H') { 
                    q.push(i, j);
                    dis[i][j] = 0;
                }
            }
        }

        
        const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (0 <= nx && nx < n && 0 <= ny && ny < m && mat[nx][ny] == '.' && dis[nx][ny] == -1) {
                    q.push(nx, ny);
                    dis[nx][ny] = dis[x][y] + 1;
                }
            }
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (dis[i][j] != -1 && dis[i][j] <= d) 
                    res++;
            }
        }
        return res;
    };
    cout << bfs() << '\n';
}

signed main() {
	IO;	
	solve();	
}
