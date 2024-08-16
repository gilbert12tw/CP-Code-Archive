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

const int mxN = 2e6 + 5;


int m;
inline void solve() {
    // i -> apple, j -> cow
    // x_i - x_j = t_i - t_j
    // x_i - t_i = x_j - t_j
    cin >> m;
    vector<array<int, 4>> v;
    for (int i = 0; i < m; i++) {
        int q, t, x, n;
        cin >> q >> t >> x >> n;
        v.pb({q, t, x, n});
    }
    sort(ALL(v), [](auto a, auto b) {
        if (a[1] == b[1]) {
            return a[0] > b[0];
        }
        return a[1] > b[1];
    });

    int ans = 0;
    multiset<pii> st;
    for (auto [q, t, x, n] : v) {
        test(q, t, x, n);
        if (q == 2) {
            st.insert(mkp(x - t, n));
        }
        else {
            auto it = st.upper_bound(mkp(x - t, INF));
            if (it == st.begin()) continue;
            it--;
            int pn = n;
            while (n > 0) {
                if (n >= it -> second) {
                    n -= it -> second;
                    it = st.erase(it);
                    it--;
                }
                else {
                    pii prv = *it;
                    st.erase(it);
                    st.insert({prv.first, prv.second - n});
                    n = 0;
                    break;
                }
                if (it == st.begin()) break;
            }
            test(pn - n);
            ans += (pn - n); 
        }
    }
    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
