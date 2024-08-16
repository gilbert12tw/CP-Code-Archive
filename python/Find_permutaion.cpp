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
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

struct linear_base {
    int bas[35] = {}, dim = 0;	
    const int mxL = 32;
    bool insert(int x) {
        for (int i = mxL; i >= 0; i--) {
            if (((x>>i) & 1) == 0)
                continue; 
            // x 的第 i 個 bit 是 1
            if (bas[i] == 0) { // 加入成為新的 bas[i]
                bas[i] = x;
                dim++;
                return 1;
            }
            x ^= bas[i]; // xor 完繼續往下檢查
        }
        return 0; // 沒有成功 insert
    }
};

inline void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> pm;
    for (int i = 0; i < n - k; i++) pm.eb(0);
    for (int i = 0; i < k; i++) pm.eb(1);

    vector<int> ans;
    linear_base basis;
    do {
        int res = 0;
        for (int i = 0; i < n; i++) res |= (pm[i] << i);
        test(res);
        if (basis.insert(res)) ans.eb(res); 
    } while (next_permutation(ALL(pm)));
    if (SZ(ans) < n) { 
        cout << "NO\n";
    } else {
        cout << "YES\n";
        vector<int> seq;
        for (int i = 0; i < (1<<n); i++) {
            int res = i ^ (i >> 1);
            seq.eb(res);
        }

        for (int i : seq) { 
            int res = 0;
            for (int j = 0; j < n; j++) {
                if (get_bit(i, j))
                    res ^= ans[j];
            }
            cout << res << '\n';
        }
    }
}

signed main() {
    IO;	
    solve();	
}
