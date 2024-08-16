#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define x first
#define y second
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
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

inline void solve() {
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> a(n), b(m);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;
    map<int, int> mp;
    for (int i = 0; i < l; i++) {
        int c, d; cin >> c >> d;
        mp[a[c - 1] + b[d - 1]]++;
    }
    
    sort(ALL(a), greater<int>());
    sort(ALL(b), greater<int>());
    priority_queue<pii> pq;
    for (int i = 0; i < n; i++) {
        pq.push(a[i] + b[0], 0);
    }
    while (!pq.empty()) {
        auto [sum, idb] = pq.top(); pq.pop();
        if (mp[sum] == 0) {
            cout << sum << '\n';
            return;
        }
        mp[sum]--;
        int aval = sum - b[idb];
        if (idb != m - 1) 
            pq.push(aval + b[idb + 1], idb + 1);
    }
}

signed main() {
	IO;	
	solve();	
}
