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

inline void solve() {
    int n, m;
    string s, t;
    cin >> n >> m;
    cin >> s >> t;
    
    vector<int> ok(n), ed(n);

    if (s[0] != t[0] || s[n-1] != t[m-1]) {
        cout << "No\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        if (i == 0 || ok[i-1]) {
            for (int j = 0; j < m; j++) {
                if (i + j < n && s[i+j] == t[j]) {
                    ok[i+j] = 1;
                    if (j == m - 1)
                        ed[i+j] = 1;
                } else break;
            }
        }
        if (i == 0 || ed[i-1]) {
            for (int j = i - m + 1; j <= i; j++) {
                if (j < 0) continue;
                for (int k = 0; k < m; k++) {
                    if (j + k < i) continue;
                    if (j + k < n && s[j+k] == t[k]) {
                        ok[j+k] = 1;
                        if (k == m - 1)
                            ed[j+k] = 1;
                    } else break;
                }
            }
        }
    }
    int check = 1;
    for (int i = 0; i < n; i++) if (!ok[i]) check = 0;

    if (check) cout << "Yes\n";
    else cout << "No\n";

}

signed main() {
	IO;	
	solve();	
}
