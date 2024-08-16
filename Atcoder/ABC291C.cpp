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

const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

inline void solve() {
    int n;
    string s;
    cin >> n >> s;

    int x = 0, y = 0;
    set<pii> st;
    st.insert(mkp(0, 0));
    map<char, int> mp;
    mp['L'] = 0;
    mp['U'] = 1;
    mp['R'] = 2;
    mp['D'] = 3;
    int ok = 0;
    for (int i = 0; i < n; i++) {
        x += dx[mp[s[i]]]; 
        y += dy[mp[s[i]]];
        if (st.find(mkp(x, y)) != st.end()) ok = 1; 
        st.insert(mkp(x, y));
    }
    cout << (ok ? "Yes\n" : "No\n");

}

signed main() {
	IO;	
	solve();	
}
