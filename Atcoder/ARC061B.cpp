#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
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
    int h, w, n;
    cin >> h >> w >> n;
    set<pii> st;
    map<pii, int> mp;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        mp[mkp(x, y)] = 1;
        
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                if (x + j <= 1 or x + j >= h or y + k <= 1 or y + k >= w) 
                    continue;
                st.insert(mkp(x + j, y + k));
            }
        }
    }

    int total = (h - 2) * (w - 2);

    map<int, int> ans;
    for (auto [x, y] : st) {
        int cnt = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (mp.find(mkp(x + i, y + j)) != mp.end())
                    cnt++;
            }
        }
        ans[cnt]++;
    }
    cout << total - SZ(st) << '\n';
    for (int i = 1; i <= 9; i++) 
        cout << ans[i] << '\n';

}

signed main() {
	IO;	
	solve();	
}
