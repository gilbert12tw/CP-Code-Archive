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
    int n; cin >> n;
    vector<int> a(n), b(n), cnta(n + 1), cntb(n + 1);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;

    for (int i = 0; i < n; i++) {
        cnta[a[i]]++;
        cntb[b[i]]++;
    }
    int mx = 0;
    for (int i = 0; i < n; i++) {
        mx = max(mx, min(cnta[a[i]], cntb[b[i]]));
    }
    if (mx * 2 > n) {
        cout << "No\n";
        return;
    }

    vector<int> trash_pos(n), trash_val, used;
    for (int i = 0; i < n; i++) {
        if (cntb[a[i]]) {
            cntb[a[i]]--;
            used.eb(a[i]);
        } else {
            trash_pos[i] = 1;
        }
        if (cnta[b[i]])
            cnta[b[i]]--;
        else 
            trash_val.eb(b[i]);
    }
    
    int st = SZ(used) / 2;

    for (int i = 0; i < n; i++) {
        if (trash_pos[i]) {
            cout << trash_val.back() << ' ';
            trash_val.pop_back();
        } else {
            cout << used[st] << ' ';
            st = (st + 1) % SZ(used);
        }
    }
}

signed main() {
	IO;	
	solve();	
}
