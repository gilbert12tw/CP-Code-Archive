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

int n, k;

int ask(vector<int> &v) {
    cout << "? ";
    for (int i : v) cout << i << ' ';
    cout << endl;
    int x; cin >> x;
    return x;
}

inline void solve() {
    cin >> n >> k;
    vector<int> v;
    for (int i = 1; i <= k; i++) v.eb(i);
    int pp = ask(v);
    v.clear();
    for (int i = 2; i <= k; i++) v.eb(i);
    v.eb(n);
    int gg = ask(v);
    vector<int> a(n + 1);
    a[n] = gg ^ pp;

    v.clear();
    for (int j = 2; j <= k; j++) v.eb(j);
    v.eb(0);
    for (int i = k + 1; i < n; i++) {
        v.pop_back();
        v.eb(i);
        a[i] = ask(v) ^ pp;
    }
    
    for (int i = 2; i <= k; i++) {
        v.clear();
        for (int j = 1; j <= k; j++) {
            if (j == i) continue;
            v.eb(j);
        }
        v.eb(n);
        int x = ask(v);
        a[i] = (a[n] ^ x ^ pp);
    }

    v.clear();
    int sum = 0;
    for (int i = 1; i <= k; i++) sum += a[i];
    if (sum % 2 == pp) {
        cout << "! ";
        for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    } else {
        cout << "! ";
        for (int i = 1; i <= n; i++) cout << (a[i]^1) << ' ';
    }
    cout << endl;
}

signed main() {
	IO;	
	solve();	
}
