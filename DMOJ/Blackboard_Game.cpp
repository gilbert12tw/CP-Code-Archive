#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<numeric>
#include<assert.h>
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

int n;
map<vector<int>, int> dp;



vector<int> count_div(int a) {

    vector<int> res;
    for (int i = 2; i * i <= a && a != 1; i++) {
        int cnt = 0;
        if (a % i) continue;
        while (a % i == 0) {
            a /= i;
            cnt++;
        }
        if (cnt > 1) res.eb(cnt);
    }
    sort(ALL(res));
    return res;
}

int sol(int a) {
    vector<int> div = count_div(a);
    if (dp.find(div) != dp.end()) 
        return dp[div];

    vector<int> mex;
    for (int i = 2; i * i <= a; i++) {
        if (a % i || gcd(i, a / i) == 1) continue;
        mex.eb(sol(i) ^ sol(a / i));
    }
    sort(ALL(mex));
    unique(ALL(mex));
    for (int i = 0; i < SZ(mex); i++) {
        if (i != mex[i]) return dp[div] = i;
    }
    return dp[div] = SZ(mex);
}


inline void solve() {
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        ans ^= sol(a);
    }
    if (ans) cout << "ALICE\n";
    else cout << "BOB\n";
}

signed main() {
	IO;	
	solve();	
}
