#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
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

vector<vector<int>> all_cy = {
    {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4},
    {1, 2, 3}, {1, 3, 2}, {1, 2, 4}, {1, 4, 2}, {1, 3, 4}, {1, 4, 3}, {2, 3, 4}, {2, 4, 3},
    {1, 2, 3, 4}, {1, 3, 2, 4}, {1, 3, 4, 2}, {1, 2, 4, 3}, {1, 4, 3, 2}, {1, 4, 2, 3}
};

inline void solve() {
    int n; cin >> n;
    vector<int> a(n), b;
    for (int &i : a) cin >> i;
    b = a;
    sort(ALL(b));
    

    multiset<pii> edge;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            edge.insert(mkp(a[i], b[i]));
        }
    }

    int edge_cnt = SZ(edge);
    int cyc_cnt = 0;
    while (!edge.empty()) {
        for (auto cyc : all_cy) {
            int ok = 1;
            for (int i = 1; i <= SZ(cyc); i++) {
                if (edge.find(mkp(cyc[i-1], cyc[i % SZ(cyc)])) == edge.end()) {
                    ok = 0;
                    break;
                }
            }
            
            if (ok) {
                for (int i = 1; i <= SZ(cyc); i++) {
                    edge.erase(edge.find(mkp(cyc[i-1], cyc[i % SZ(cyc)])));
                }
                break;
            }
        }
        cyc_cnt++;
    }
    cout << edge_cnt - cyc_cnt;
}

signed main() {
	IO;	
	solve();	
}
