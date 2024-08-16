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

const int mxN = 4e5 + 5;
int seg[mxN * 4], tag[mxN * 4];

#define ls (x<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)

int n;
void up(int x, int l, int r) {
    if (tag[x] > 0) seg[x] = (r - l + 1);
    else seg[x] = seg[ls] + seg[rs];
}

void modify(int a, int b, int v, int l = 1, int r = n, int x = 1) {
    if (a > b) return;
    if (a <= l && r <= b) {
        tag[x] += v;
        up(x, l, r);
        return;
    }
    if (a <= mid) modify(a, b, v, l, mid, ls);
    if (b > mid) modify(a, b, v, mid+1, r, rs);
    up(x, l, r);
}

inline void solve() {
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    map<int, int> mp;
    vector<int> nxt(n + 1), lst(n + 1);
    for (int i = 1; i <= n; i++) {
        lst[i] = mp[a[i]];
        mp[a[i]] = i;
    }
    mp.clear();
    for (int i = n; i >= 1; i--) {
        nxt[i] = (mp.find(a[i]) == mp.end() ? n + 1 : mp[a[i]]);
        mp[a[i]] = i;
    }

    vector<vector<array<int, 3>>> qry(n + 2);
    for (int i = 1; i <= n; i++) {
        qry[i].pb({lst[i] + 1, i, 1});
        qry[nxt[i]].pb({lst[i] + 1, i, -1});
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (auto q : qry[i]) {
            modify(q[0], q[1], q[2]);
        }
        ans += seg[1];
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
