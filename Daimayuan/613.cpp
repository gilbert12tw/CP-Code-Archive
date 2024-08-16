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
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

int good = 1;
void dfs(vector<pii> &v, int l, int r) {
    if (r <= l) return;

    int ok = -1;
    int k = l, j = r, clk = 0;
    while (k <= j) {
        int i;
        if (clk) i = k++;
        else i = j--;
        clk ^= 1;

        int ll = v[i].F, rr = v[i].S;
        if (ll <= l && rr >= r) {
            ok = i;
            break;
        }
    }

    if (ok == -1) {
        good = 0;
        return;
    }
    dfs(v, l, ok - 1);
    dfs(v, ok + 1, r);
}

inline void solve() {
    int n; cin >> n;
    vector<int> a(n), lst(n), nxt(n);
    for (int &i : a) cin >> i;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        if (mp.find(a[i]) == mp.end()) 
            lst[i] = 0;
        else lst[i] = mp[a[i]] + 1;
        mp[a[i]] = i;
    }
    mp.clear();
    for (int i = n - 1; i >= 0; i--) {
        if (mp.find(a[i]) == mp.end()) 
            nxt[i] = n - 1;
        else nxt[i] = mp[a[i]] - 1;
        mp[a[i]] = i;
    }

    vector<pii> v;
    for (int i = 0; i < n; i++) { 
        v.eb(lst[i], nxt[i]);
    }
    good = 1;
    dfs(v, 0, n - 1);
    if (!good) cout << "boring\n";
    else cout << "non-boring\n";
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
