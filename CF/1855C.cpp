#include<bits/stdc++.h>
//#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
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

int n;

vector<pii> sol1(vector<int> a) {
    vector<pii> ans;
    int mx_id = -1, mn_id = -1;
    for (int i = 0; i < n; i++) {
        if (mx_id == -1 || a[mx_id] <= a[i]) mx_id = i;
        if (mn_id == -1 || a[mn_id] > a[i]) mn_id = i;
    }

    while (a[mn_id] + a[mx_id] > 0) {
       ans.eb(mn_id, mn_id); 
       a[mn_id] += a[mn_id];
    }
    for (int i = 0; i < n; i++) if (a[i] > 0) {
        ans.eb(i, mn_id);
        a[i] += a[mn_id];
    }
    for (int i = n - 1; i >= 0; i--) {
        if (i != n-1 && a[i+1] < a[i]) {
            a[i] += a[mn_id];
            ans.eb(i, mn_id);
        }
        if (a[i] <= a[mn_id])
            mn_id = i;
    }
    return ans;
}

vector<pii> sol2(vector<int> a) {
    vector<pii> ans;
    int mx_id = -1, mn_id = -1;
    for (int i = 0; i < n; i++) {
        if (mx_id == -1 || a[mx_id] <= a[i]) mx_id = i;
        if (mn_id == -1 || a[mn_id] > a[i]) mn_id = i;
    }

    while (a[mx_id] + a[mn_id] < 0) {
        ans.eb(mx_id, mx_id);
        a[mx_id] += a[mx_id];
    }
    for (int i = 0; i < n; i++) if (a[i] < 0) {
        ans.eb(i, mx_id);
        a[i] += a[mx_id];
    }
    for (int i = 0; i < n; i++) {
        if (i && a[i] < a[i-1]) {
            a[i] += a[mx_id];
            ans.eb(i, mx_id);
        }
        if (a[i] >= a[mx_id])
            mx_id = i;
    }
    return ans;
}

inline void solve() {
    cin >> n;
    vector<int> a(n);
    vector<pii> ans;

    int mx_id = -1, mn_id = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (mx_id == -1 || a[mx_id] <= a[i]) mx_id = i;
        if (mn_id == -1 || a[mn_id] > a[i]) mn_id = i;
    }

    if (a[mn_id] >= 0) {
        for (int i = 0; i < n; i++) {
            if (a[i] < a[mx_id]) {
                a[i] += a[mx_id];
                ans.eb(i, mx_id);
            }
            mx_id = i;
        }
    } else if (a[mx_id] <= 0) {
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] > a[mn_id]) {
                a[i] += a[mn_id];
                ans.eb(i, mn_id);
            }
            mn_id = i;
        }
    } else {
        vector<pii> tmp = sol1(a);
        ans = sol2(a);
        if (SZ(tmp) < SZ(ans))
            ans = tmp;
    }

    for (auto [x, y] : ans) a[x] += a[y];


   for (int i = 0; i < n; i++) { 
        test(i, a[i]);
        //if (i && a[i-1] > a[i]) cout << "fuck\n";
    } 
    assert(SZ(ans) <= 31);
    cout << SZ(ans) << '\n';
    for (auto [a, b] : ans) cout << a+1 << ' ' << b+1 << '\n';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
