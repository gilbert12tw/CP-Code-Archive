#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define x first
#define y second
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
    int n;
    cin >> n;
    vector<string> mat(n);
    for (int i = 0; i < n; i++) cin >> mat[i];

    vector<pii> candi;
    vector<vector<int>> vis(n, vector<int>(n));
    candi.eb(0, 0);
    vis[0][0] = 1;
    string ans;
    ans += mat[0][0];
    while (!candi.empty()) {
        char mn = 'Z';
        for (auto pos : candi) {
            if (pos.x + 1 < n && mat[pos.x+1][pos.y] < mn) 
                mn = mat[pos.x+1][pos.y];
            if (pos.y + 1 < n && mat[pos.x][pos.y+1] < mn) 
                mn = mat[pos.x][pos.y+1];
        }

        vector<pii> nxt_que;
        for (auto pos : candi) {
            if (pos.x + 1 < n && mat[pos.x+1][pos.y] == mn) {
                if (!vis[pos.x+1][pos.y]) {
                    vis[pos.x+1][pos.y] = 1;
                    nxt_que.eb(pos.x+1, pos.y);
                }
            }

            if (pos.y + 1 < n && mat[pos.x][pos.y+1] == mn) {
                if (!vis[pos.x][pos.y+1]) {
                    vis[pos.x][pos.y+1] = 1;
                    nxt_que.eb(pos.x, pos.y+1);
                }
            }
        }
        if (!nxt_que.empty()) ans += mn;
        candi = move(nxt_que);
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
