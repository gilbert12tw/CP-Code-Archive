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

inline void solve() {
    int n;
    cin >> n;
    string s; 
    cin >> s;
    int q;
    cin >> q;
    vector<int> c(n);
    vector<int> op(q);
    for (int i = 0; i < q; i++) {
        int t, x;
        char cx;
        cin >> t >> x >> cx;
        op[i] = t;
        if (t == 1) {
            c[x-1] = i;
            s[x-1] = cx;
        } 
    }

    int lst = -1, tm = -1;
    for (int i = q - 1; i >= 0; i--) {
        if (op[i] == 1) continue;
        if (op[i] == 2) {
            lst = 2;
            tm = i;
            break;
        } else {
            lst = 3;
            tm = i;
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        if (c[i] < tm) {
            if (lst == 2) {
                s[i] = tolower(s[i]);
            } else {
                s[i] = toupper(s[i]);
            }
        }
    }
    cout << s;
}

signed main() {
	IO;	
	solve();	
}
