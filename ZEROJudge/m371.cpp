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

const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m, 0));
    vector<vector<int>> del(n, vector<int>(m, 0));
    int ans = 0;

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) 
        cin >> mat[i][j];

    auto check = [&](int x, int y) {
        return (x >= 0 && x < n && y >= 0 && y < m);
    };
    while (1) {
        int del_cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (del[i][j]) continue;
                for (int d = 0; d < 4; d++) {
                    int x = i + dx[d], y = j + dy[d];
                    while (check(x, y) && del[x][y]) {
                        x += dx[d];
                        y += dy[d];
                    }
                    if (check(x, y) && mat[x][y] == mat[i][j]) {
                        ans += mat[i][j];
                        del[x][y] = del[i][j] = 1;
                        del_cnt++;
                        break;
                    }
                }
            }
        }
        if (del_cnt == 0) break;
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
