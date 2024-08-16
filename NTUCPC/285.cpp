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
    int n; cin >> n;
    vector<int> a(n), pa(n, -1), dep(n);
    queue<int> q;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0) q.push(i);
        else pq.push(a[i], i);
    }
    
    int ans = 1;
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        //test(q.front());
        if (!pq.empty()) {
            auto [ad, v] = pq.top(); pq.pop();
            test(ad, u, v);
            ad--;
            pa[u] = v;
            dep[v] = max(dep[u] + 1, dep[v]);
            ans = max(ans, dep[v]);
            if (ad > 0) {
                pq.push(ad, v);
            } else {
                q.push(v);
            }
        }
    }
    test(SZ(pq), SZ(q));
    cout << ans << '\n';
    for (int i : pa) cout << i+1 << ' ';
}

signed main() {
	IO;	
    int T; cin >> T;
	while (T--) solve();	
}
