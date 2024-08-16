#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
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

inline void solve() {
    string s, t;
    cin >> s >> t;
    map<char, int> mps, mpt;
    int ans = 1;
    for (char c : s) {
        mps[c]++;
    }
    for (char c : t) {
        mpt[c]++;
    }
    for (char c : "atcoder") {
        if (mps[c] > mpt[c]) mpt['@'] -= (mps[c] - mpt[c]);
        else if (mps[c] < mpt[c]) mps['@'] -= (mpt[c] - mps[c]);
        mps[c] = mpt[c] = 0;
    }
    for (char c = 'a'; c <= 'z'; c++) if (mps[c] != mpt[c]) ans = 0;
    if (mps['@'] != mpt['@'] || mps['@'] < 0 || mpt['@'] < 0) ans = 0;
    cout << (ans ? "Yes" : "No");
}

signed main() {
	IO;	
	solve();	
}
