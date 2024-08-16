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

// BCC
int n, m;
int df, dep[mxN], low[mxN], bcc[mxN], cc;
int eu[mxN], ev[mxN];
vector<int> g[mxN], tr[mxN];
vector<int> stk;
vector<int> ans;
bitset<mxN> vis;

void tarjan(int u, int e = -1){
	dep[u] = low[u] = ++df;
	stk.pb(u);


    
    int go_cnt = 0, isAP = 0;
	for(int i : g[u]){
		int v = eu[i] ^ ev[i] ^ u;
        if (vis[i]) continue;
        vis[i] = 1;
		if (i == e) continue;
        go_cnt++; // 只向下搜了一次
		if(!dep[v]){
			tarjan(v, i);
			low[u] = min(low[u], low[v]);
		} else {
			low[u] = min(low[u], dep[v]);
		}
        if (low[v] >= dep[u]) isAP = 1;
	}

    if ((e != -1 && isAP) || (e == -1 && go_cnt > 1)) {
        ans.eb(u);
    }
}

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        g[eu[i]].eb(i);
        g[ev[i]].eb(i);
    }

    for (int i = 1; i <= n; i++) {
        if (!dep[i]) { 
            tarjan(i);
        }
    }
    cout << SZ(ans) << '\n';
    for (int i : ans) cout << i << ' ';
}

signed main() {
	IO;	
	solve();	
}
