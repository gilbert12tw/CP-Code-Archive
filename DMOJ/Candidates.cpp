#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
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

inline void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) {
        int rk; cin >> rk;
        pos[rk] = i;
    }
    vector<vector<int>> r(n, vector<int>(k));
    for (int i = 1; i <= n; i++) {
        for (int &i : r[pos[i]]) cin >> i;
    }

    vector<int> ind(k);
    vector<vector<int>> bad(n);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < k; j++) {
            if (r[i][j] > r[i-1][j]) {
                ind[j]++;
                bad[i].eb(j);
            }
        }
    }
    
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k; i++) {
        //test(ind[i]);
        if (ind[i] == 0) pq.push(i);
    }

    vector<int> ans;
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        //test(u);
        ans.eb(u + 1);
        for (int i = 1; i < n; i++) {
            if (r[i-1][u] > r[i][u]) {
                for (int j : bad[i]) {
                    ind[j]--;
                    if (ind[j] == 0) pq.push(j);
                }
                bad[i].clear();
            }
        }
    }
    if (SZ(ans) != k) {
        cout << -1 << '\n';
        return;
    }
    for (int i : ans) cout << i << ' ';
}

signed main() {
	IO;	
	solve();	
}
