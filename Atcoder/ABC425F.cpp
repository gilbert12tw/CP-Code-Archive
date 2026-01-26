#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma loop-opt(on)
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
#define mod 998244353
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


const int mxL = 6e6 + 1;
struct Trie {
    int tr[mxL][26], tot = 0;
    int isEnd[mxL];
    int id[mxL];
    int idx_cnt = 0;

    int insert(string &s) {
        int cur = 0;
        for (char c : s) {
            int idc = c - 'a';
            int &nxt = tr[cur][idc];
            if (!nxt) nxt = ++tot;
            cur = nxt;
        }
        if (isEnd[cur] == 0) {
            id[cur] = ++idx_cnt;
        }
        isEnd[cur] = 1;
        return id[cur];
    }

    int get(string &s) {
        int cur = 0;
        for (char c : s) {
            int idc = c - 'a';
            int &nxt = tr[cur][idc];
            if (!nxt) return -1;
            cur = nxt;
        }
        return id[cur];
    }
} trie;

inline void solve() {
    int n; 
    cin >> n;
    string s;
    cin >> s;

    vector<int> dp(1<<n);
    for (int i = 1; i < (1<<n); i++) {
        if ((i & (i - 1)) == 0) {
            dp[i] = 1;
            continue;
        }
        char pre = '.';
        for (int j = 0; j < n; j++) {
            if (get_bit(i, j) && pre != s[j]) {
                dp[i] = (dp[i] + dp[i ^ (1<<j)]) % mod;
                pre = s[j];
            }
        }
    }

    cout << dp[(1<<n)-1] << '\n';
}

signed main() {
    IO;	
    solve();	
}
