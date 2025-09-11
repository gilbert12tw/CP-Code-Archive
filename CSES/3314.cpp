#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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
#define MOD 998244353
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 2e5 + 5;
struct Cartesian_Tree { // Root is Maximum
    int n, root;
    vector<int> w, rs, ls;
    Cartesian_Tree(int _n): n(_n), root(-1), rs(n, -1), ls(n, -1) {}

    void build(const vector<int> &we) {
        w = we;                 
        vector<int> stk;         
        for (int i = 0; i < n; i++) {
            int last = -1;
            while (!stk.empty() && w[stk.back()] < w[i]) {
                last = stk.back();
                stk.pop_back();
            }
            if (stk.empty()) {
                root = i;
            } else {
                rs[stk.back()] = i;
            }
            if (last != -1) {
                ls[i] = last;
            }
            stk.push_back(i);
        }
    }

    int dfs(int u) {
        int mx = 0;
        if (ls[u] != -1) {
            int t = dfs(ls[u]);
            mx = t + (w[u] != w[ls[u]]);
        }
        if (rs[u] != -1) {
            int t = dfs(rs[u]);
            mx = max(mx, t + (w[u] != w[rs[u]]));
        }
        return mx;
    }
};

inline void solve() {
    int n; cin >> n;
    vector<int> a(n), stk;
    for (int &i : a) cin >> i;

    Cartesian_Tree tree(n);
    tree.build(a);

    cout << tree.dfs(tree.root) + 1 << '\n';
}

signed main() {
    IO;	
    solve();	
}
