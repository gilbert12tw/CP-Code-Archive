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
    vector<int> a(n), b(n), c(n);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;
    for (int &i : c) cin >> i;

    sort(ALL(a), greater<int>());
    sort(ALL(b), greater<int>());
    sort(ALL(c), greater<int>());

    #define pp pair<int, array<int, 3>>
    priority_queue<pp> pq;

    auto cal = [&](const array<int, 3> &ar) -> int {
        int i = ar[0], j = ar[1], k = ar[2];
        return a[i] * b[j] + b[j] * c[k] + a[i] * c[k];
    };

    auto hsh = [&](const array<int, 3> &a) -> int {
        int i = a[0], j = a[1], k = a[2];
        return i * n * n + j * n + k;
    };

    array<int, 3> st = {0, 0, 0};
    unordered_map<int, int> mp;
    pq.push(mkp(cal(st), st));
    mp[hsh(st)] = 1;
    
    int cnt = 0;
    while (!pq.empty()) {
        auto u = pq.top(); pq.pop();
        if (++cnt == k) {
            cout << u.first << '\n';
            return; 
        }
        test(cnt, u.first);
        for (int j = 0; j < 3; j++) {
            auto ar = u.second;
            ar[j]++;
            if (ar[j] >= n) continue;
            if (mp.find(hsh(ar)) != mp.end()) continue;
            mp[hsh(ar)] = 1;
            pq.push(mkp(cal(ar), ar));
        }
    }
}

signed main() {
	IO;	
	solve();	
}
