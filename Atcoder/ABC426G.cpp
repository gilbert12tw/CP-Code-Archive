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

const int MAX_C = 500;
inline void solve() {
    int n;
    cin >> n;
    vector<pii> item(n + 1);
    for (int i = 1; i <= n; i++) 
        cin >> item[i].first >> item[i].second;

    int q;
    cin >> q;
    struct Query {
        int l, r, c, id;
    };
    vector<Query> qry(q);
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        cin >> qry[i].l >> qry[i].r >> qry[i].c; 
        qry[i].id = i;
        if (qry[i].l == qry[i].r) {
            if (item[qry[i].l].first <= qry[i].c)
                ans[i] = item[qry[i].l].second;
        }
    }

    auto dc = [&](int l, int r, vector<Query> &qry, auto self) -> void {
        if (l == r) return;
        if (l > r || qry.empty()) return;
        int mid = (l + r) >> 1;
        // DP
        vector<vector<int>> dp((r - l + 1), vector<int>(MAX_C + 5, -INF));
        for (int i = mid; i >= l; i--) {
            int w = item[i].first, v = item[i].second;
            if (i == mid) {
                dp[i - l][0] = 0;
                dp[i - l][w] = v;
            } else {
                for (int j = 0; j <= MAX_C; j++) {
                    if (j < w) dp[i - l][j] = dp[i - l + 1][j];
                    else dp[i - l][j] = max(dp[i - l + 1][j], dp[i - l + 1][j - w] + v);
                }
            }
        }
        for (int i = mid + 1; i <= r; i++) {
            int w = item[i].first, v = item[i].second;
            if (i == mid + 1) {
                dp[i - l][0] = 0;
                dp[i - l][w] = v;
            } else {
                for (int j = 0; j <= MAX_C; j++) {
                    if (j < w) dp[i - l][j] = dp[i - l - 1][j];
                    else dp[i - l][j] = max(dp[i - l - 1][j], dp[i - l - 1][j - w] + v);
                }
            }
        }

        vector<Query> ql, qm, qr;
        for (auto qq : qry) {
            if (qq.r <= mid) {
                ql.eb(qq);
            } else if (qq.l > mid) {
                qr.eb(qq);
            } else {
                qm.eb(qq);
            }
        }
        qry.clear();
        for (auto qq : qm) {
            int c = qq.c;
            vector<int> tmpl(c + 1), tmpr(c + 1);
            for (int i = 1; i <= c; i++) {
                tmpl[i] = max(tmpl[i-1], dp[qq.l - l][i]);
                tmpr[i] = max(tmpr[i-1], dp[qq.r - l][i]);
            }
            int res = 0;
            for (int i = 0; i <= c; i++) {
                res = max(res, tmpl[i] + tmpr[c - i]);
            }
            ans[qq.id] = res;
        }
        self(l, mid, ql, self);
        self(mid + 1, r, qr, self);
    };

    dc(1, n, qry, dc);

    for (int i : ans) cout << i << '\n';
}

signed main() {
	IO;	
	solve();	
}
