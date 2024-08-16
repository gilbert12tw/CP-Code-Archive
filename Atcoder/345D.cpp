#include<bits/stdc++.h>
//#define loli
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

int n, h, w;
int a[10], b[10];

int mat[11][11];
int check(int x, int y, int a, int b) {
    if (x + a > h || y + b > w) return 0;
    for (int i = x; i < x + a; i++) 
        for (int j = y; j < y + b; j++)
            if (mat[i][j]) return 0;
    return 1;
}

void put(int x, int y, int a, int b, int v) {
    for (int i = x; i < x + a; i++) 
        for (int j = y; j < y + b; j++)
            mat[i][j] += v;
}

int ok() {
    for (int i = 0; i < h; i++) 
        for (int j = 0; j < w; j++) 
            if (mat[i][j] == 0) return 0;
    return 1;
}

int used[10];
void dfs(int chose) {
    if (ok()) {
        cout << "Yes\n";
        exit(0);
    }

    int st = -1, ed = -1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (mat[i][j] == 0) {
                st = i;
                ed = j;
                break;
            }
        }
        if (st != -1) break;
    }

    if (st == -1) return;
    test(chose, st, ed);

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;

        used[i] = 1;
        if (check(st, ed, a[i], b[i])) {
            put(st, ed, a[i], b[i], 1);
            dfs(chose + 1);
            put(st, ed, a[i], b[i], -1);
        }

        if (a[i] != b[i] && check(st, ed, b[i], a[i])) {
            put(st, ed, b[i], a[i], 1);
            dfs(chose + 1);
            put(st, ed, b[i], a[i], -1);
        }
        used[i] = 0;
    }
}

inline void solve() {
    cin >> n >> h >> w;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    dfs(0);
    cout << "No\n";
}

signed main() {
	IO;	
	solve();	
}
