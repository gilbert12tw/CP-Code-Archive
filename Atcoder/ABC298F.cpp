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

const int mxN = 2e6 + 5;

inline void solve() {
    int n; cin >> n;

    map<int, int> sumy;
    map<int, vector<pii> > mpx;
    for (int i = 0; i < n; i++) {
        int r, c, x;
        cin >> r >> c >> x;
        mpx[r].eb(c, x);
        sumy[c] += x;
    }

    multiset<int> st;

    int ans = 0;

    for (auto [id, s] : sumy) st.insert(s);
    
    for (auto [x, v] : mpx) {
        int sumx = 0;
        vector<pii> undo;
        for (auto [y, val] : v) {
            sumx += val;
            auto it = st.find(sumy[y]); 
            int newval = *it - val;
            undo.eb(newval, *it);
            st.erase(it);
            st.insert(newval);
        }

        ans = max(ans, sumx + *st.rbegin());

        for (auto [a, b] : undo) {
            st.erase(st.find(a));
            st.insert(b);
        }
    }

    cout << ans << '\n';
}

signed main() {
	IO;	
	solve();	
}
