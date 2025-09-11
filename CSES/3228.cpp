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
    int n; cin >> n;

    vector<string> b(11, string(n, '0'));
    
    auto dfs = [&](int dep, int l, int r, auto&& dfs) -> int {
        if (r <= l) return dep;
        int mid = (l + r) >> 1;
        for (int i = l; i <= mid; i++) b[dep][i] = '0';
        for (int i = mid+1; i <= r; i++) b[dep][i] = '1';
        int res = dfs(dep + 1, l, mid, dfs);
        res = max(res, dfs(dep + 1, mid + 1, r, dfs));
        return res;
    };

    int mx_dep = dfs(0, 0, n - 1, dfs);

    vector<string> ans;
    for (int i = 0; i < mx_dep; i++) {
        cout << "? " << b[i] << endl;
        string tmp;
        cin >> tmp;
        ans.eb(tmp);
    }

    vector<string> ord(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < mx_dep; j++) {
            ord[i].pb(ans[j][i]);
        }
    }
    auto dic = ord;
    sort(ALL(dic));

    cout << "! ";
    for (int i = 0; i < n; i++) {
        cout << (lower_bound(ALL(dic), ord[i]) - dic.begin()) + 1 << ' ';
    }
}

signed main() {
	IO;	
	solve();	
}
