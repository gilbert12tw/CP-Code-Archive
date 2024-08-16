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

int a[3][3];
int color[3][3];

bool check() {
    for (int i = 0; i < 3; i++) {
        if (color[0][i] == color[1][i] && color[1][i] == color[2][i] && color[0][i] != 0) return 1;
        if (color[i][0] == color[i][1] && color[i][1] == color[i][2] && color[i][0] != 0) return 1;
    }
    if (color[0][0] != 0 && color[0][0] == color[1][1] && color[1][1] == color[2][2]) return 1;
    if (color[1][1] != 0 && color[2][0] == color[1][1] && color[1][1] == color[0][2]) return 1;
    return 0;
}

bool dfs(int pos, int sum) {
    if (pos == 9) {
        return sum > 0;
    }

    if (check()) {
        return 0;
    }

    int mul = ((pos & 1) ? 1 : -1);
    test(pos, sum, mul);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (color[i][j] == 0) {
                color[i][j] = mul;
                int t = dfs(pos + 1, sum + a[i][j] * mul);
                color[i][j] = 0;
                if (t == 0) return 1;
            }
        }
    }
    return 0;
}

inline void solve() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }

    if (dfs(0, 0)) cout << "Takahashi";
    else cout << "Aoki";
}

signed main() {
	IO;	
	solve();	
}
