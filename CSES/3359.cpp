#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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

    vector<vector<int>> from(n, vector<int>(n, -1)), rk(n, vector<int>(n, 0));
    for (int len = 1; len < 2 * n - 1; len++) {
        vector<pii> tmp;
        for (int i = max(0ll, len - n + 1); i <= len && i < n; i++) {
            int j = len - i;
            int mn = inf;
            if (i != 0 && mn > rk[i-1][j]) {
                mn = rk[i-1][j];
                from[i][j] = 0;
            }
            if (j != 0 && mn > rk[i][j-1]) {
                mn = rk[i][j-1];
                from[i][j] = 1;
            }
            test(i, j, mn, from[i][j]);
            tmp.eb(mn * 1000 + (mat[i][j] - 'A'), i);
            //test(len, i);
        }
        sort(ALL(tmp));
        int cnt = 1;
        for (int i = 0; i < SZ(tmp); i++) {
            int id = tmp[i].second;
            if (i - 1 >= 0 && tmp[i].first != tmp[i-1].first) ++cnt;
            rk[id][len - id] = cnt;
        }
    }
    int x = n - 1, y = n - 1;
    string ans;
    while (x != 0 || y != 0) {
        ans.push_back(mat[x][y]);
        if (from[x][y]) {
            y--;
        } else {
            x--;
        }
    }
    ans.push_back(mat[0][0]);
    reverse(ALL(ans));
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
