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
    int h, w, m; cin >> h >> w >> m;
    vector<array<int, 3>> qry(m);
    for (auto &i : qry) {
        cin >> i[0] >> i[1] >> i[2];
    }

    reverse(ALL(qry));
    
    map<int, int> row, col, mp;
    int row_cnt = 0, col_cnt = 0;
    int row_cnt2 = 0, col_cnt2 = 0;
    mp[0] = h * w;
    for (auto i : qry) {
        if (i[0] == 1) {
            int x = i[1], c = i[2];
            if (row.find(x) != row.end()) continue;
            if (c != 0) { 
                mp[0] -= (w - col_cnt);
                mp[c] += (w - col_cnt);
                row_cnt2++;
            } else {
                //mp[0] += col_cnt2;
            }
            row_cnt++;
            row[x] = c;
        } else {
            int x = i[1], c = i[2];
            if (col.find(x) != col.end()) continue;
            if (c != 0) {
                mp[0] -= (h - row_cnt);
                mp[c] += (h - row_cnt);
                col_cnt2++;
            } else {
                //mp[0] += row_cnt2;
                //test(row_cnt2);
            }
            col_cnt++;
            col[x] = c;
        }
        //test(i[0], i[1], i[2], mp[0]);
    }
    int res = 0;
    for (auto [x, y] : mp) if (y > 0) res++;
    cout << res << '\n';
    for (auto [x, y] : mp) {
        if (y > 0) cout << x << ' ' << y << '\n';
    }
}

signed main() {
	IO;	
	solve();	
}
