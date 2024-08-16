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
    int n; 
    cin >> n;
    map<int, vector<int>> add, del;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        if (r[i] <= l[i]) swap(l[i], r[i]);
        add[l[i]].eb(i);
        del[r[i]].eb(i);
    }
    multiset<int> st;
    bool gg = 0;
    for (int i = 1; i <= 2 * n; i++) {
        int mn = 8 * n;
        if (!st.empty()) mn = *st.begin();
        for (int id : add[i]) {
            st.insert(r[id]);
            if (r[id] >= mn) gg = 1;
        }

        for (int id : del[i]) {
            st.erase(st.find(r[id]));
        }
    }
    cout << (gg == 0 ? "No" : "Yes");
}

signed main() {
	IO;	
	solve();	
}
