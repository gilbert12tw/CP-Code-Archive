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

int n, m;
vector<int> g[mxN], gp[mxN];

inline void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') {
                g[i].eb(i + j + 1);
                gp[i + j + 1].eb(i);
            }
        }
    }

    vector<int> dis(n, inf), rdis(n, inf);
    queue<int> q;
    q.push(0);
    dis[0] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            } 
        }
    }

    q.push(n-1);
    rdis[n-1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : gp[u]) {
            if (rdis[v] > rdis[u] + 1) {
                rdis[v] = rdis[u] + 1;
                q.push(v);
            } 
        }
    }
    
    for (int i = 1; i < n - 1; i++) {
        int ans = inf;
        for (int l = max(0ll, i - m); l < i; l++) {
            for (int v : g[l]) {
                if (v > i) ans = min(ans, dis[l] + rdis[v] + 1);
            }
        }
        if (ans == inf) ans = -1;
        cout << ans << ' ';
    }
}

signed main() {
	IO;	
	solve();	
}
