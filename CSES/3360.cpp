#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
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

int n, k;
bitset<3000> cnt[3001];
char mat[3001][3001];
vector<int> col[26][3001];

inline bool check(int c) {
    for (int i = 0; i < n; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) {
        int m = SZ(col[c][i]);
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < j; k++) {
                if (cnt[col[c][i][k]][col[c][i][j]]) return true;
                cnt[col[c][i][k]][col[c][i][j]] = 1;
            }
        }
    }
    return false;
}

inline void solve() {
    cin >> n >> k;
    vector<int> cntAlpha(30);
    for (int i = 0; i < n; i++) {
        cin >> mat[i];
        for (int j = 0; j < n; j++) {
            col[(mat[i][j] - 'A')][i].eb(j);
        }
    }

    for (int i = 0; i < k; i++) {
        cout << (check(i) ? "YES" : "NO") << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
