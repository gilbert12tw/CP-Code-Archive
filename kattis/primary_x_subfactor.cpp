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

int p[30];
int ans = 0;
vector<int> stk, seq;

inline int get(int l, int r, vector<int> &v) {
    assert(r < SZ(v));
    assert(l >= 0);
    int res = 0;
    for (int i = r; i >= l; i--) res = res * 10 + v[i];
    return res;
}

inline int del(int l, int r, vector<int> &v) {
    assert(r < SZ(v));
    assert(l >= 0);
    int res = 0;
    for (int i = SZ(v) - 1; i >= 0; i--) if (i < l || i > r) res = res * 10 + v[i];
    return res;
}

void dfs(int u, int len) {
    stk.eb(u);
    if (len > ans) {
        seq = stk;
        ans = len;
    } else if (len == ans) {
        seq = min(seq, stk);
    }
    
    int tmp = u;
    vector<int> dig;
    while (tmp) {
        dig.eb(tmp % 10);
        tmp /= 10;
    }

    for (int i = 0; i < SZ(dig); i++) {
        for (int j = i; j < SZ(dig); j++) {
            if (dig[j] == 0 || (i == 0 && j == SZ(dig) - 1)) continue;
            int nxt = get(i, j, dig);
            if (nxt > 1 && u % nxt == 0) {
                dfs(del(i, j, dig), len + 1);
            }
        }
    }
    stk.pop_back();
}

inline void solve() {
    int n;
    p[0] = 1;
    for (int i = 1; i <= 12; i++) p[i] = p[i-1] * 10;

    while (cin >> n && n != 0) {
        ans = 0; seq.clear();
        stk.clear();
        dfs(n, 1);
        for (int i : seq) cout << i << ' ';
        cout << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
