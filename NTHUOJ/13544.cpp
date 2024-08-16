#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
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

const int mxN = 1001;

int n, m, a, b;
vector<int> p1[mxN], p2[mxN];

inline void solve() {
    map<char, int> mp;
    mp['A'] = 0;
    mp['F'] = 1;
    mp['H'] = 2;
    mp['S'] = 3;

    cin >> a >> n;
    for (int i = 0; i < n; i++) {
        int t; string s;
        cin >> t >> s;
        p1[t].eb(mp[s[0]]); 
    }
    cin >> b >> m;
    for (int i = 0; i < m; i++) {
        int t; string s;
        cin >> t >> s;
        p2[t].eb(mp[s[0]]); 
    }
    
    vector<int> s1(4), s2(4), ans;
    for (int i = 0; i <= min(a, b); i++) {
        for (int j : p1[i]) s1[j]++; 
        for (int j : p2[i]) s2[j]++;
        if ((!s1.empty()) && s1 == s2) {
            ans.eb(i);
        }
    }
    cout << SZ(ans) << '\n';
    for (int i = 0; i < SZ(ans); i++) cout << ans[i] << " \n"[i == SZ(ans)-1];
}

signed main() {
	IO;	
	solve();	
}
