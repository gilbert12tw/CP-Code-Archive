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

const int L = 31;

inline void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);

    vector<array<int, 2>> trie(n * 35);
    int tot_node = 0;

    auto insert = [&](int num) -> void {
        int cur = 0;
        for (int i = 31; i >= 0; i--) {
            int b = get_bit(num, i);
            if (!trie[cur][b])
                trie[cur][b] = ++tot_node;
            cur = trie[cur][b];
        }
    };

    for (int &i : a) {
        cin >> i;
        insert(i);
    }

    auto dfs = [&](int m, int cur_node, int pos, auto && self) -> int {
        if (cur_node == 0 && pos != L) return 0;
        if (m <= 0 || pos == -1) {
            //test(m, cur_node, pos);
            return 0;
        }
        int msk = (1ll<<pos);
        int lm = (m >= msk ? msk - 1 : m); 
        int res = 0;
        if (trie[cur_node][0]) {
            if (lm) res += self(lm, trie[cur_node][0], pos - 1, self);
        } else {
            if (lm) res += self(lm, trie[cur_node][1], pos - 1, self) + msk * (lm + 1);
        }
        if (trie[cur_node][1]) {
            if (m >= lm) res += self(m - lm - 1, trie[cur_node][1], pos - 1, self);
        } else {
            if (m >= lm) res += self(m - lm - 1, trie[cur_node][0], pos - 1, self) + msk * (m - lm);
        }
        return res;
    };


    cout << dfs(m - 1, 0, L, dfs) << '\n';
}

signed main() {
	IO;	
	solve();	
}
