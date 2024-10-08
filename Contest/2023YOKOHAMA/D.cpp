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

int n;
char s[205];
string opt[205][205];

inline int check(int a, int b, int k) {
    if (a + k > n || b + k > n) return 0;
    return memcmp(s + a, s + b, k) == 0;
}

inline void solve() {
    cin >> s;
    n = strlen(s);

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            for (int k = i; k <= j; k++) {
                opt[i][j].push_back(s[k]);
            }
        }
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                if (SZ(opt[i][k]) + SZ(opt[k+1][j]) < SZ(opt[i][j])) {
                    opt[i][j] = opt[i][k] + opt[k+1][j];
                }
            }
            for (int k = 2; k <= 9; k++) {
                int r = i + k * len - 1;
                if (check(i, i + (k - 1) * len, len)) {
                    if (SZ(opt[i][r]) > SZ(opt[i][j]) + 3) {
                        string tmp; tmp.push_back('0' + k);
                        opt[i][r] = tmp + "(" + opt[i][j] + ")";
                    }
                } else break;
            }
        }
    }
    cout << opt[0][n-1] << '\n';
}

signed main() {
	IO;	
	solve();	
}
