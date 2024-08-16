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

struct auto_AC_machine {
	static const int mxN = 1e6 + 5;
	int trie[mxN][26], ed[mxN], fail[mxN], dp[mxN], tot; 
	inline int insert(string &s) {
		int u = 0;
		for(auto i : s) {
			if(!trie[u][i - 'a']) trie[u][i - 'a'] = ++tot;
			u = trie[u][i - 'a'];
            dp[u]++;
		}
		return u;
	}
	 
	int topo[mxN], tp;
	inline void build() {
		queue<int> q; q.push(0);
		tp = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			topo[tp++] = u;
			for(int i = 0; i < 26; i++) {
				int &to = trie[u][i];
				if(to) {
					fail[to] = (u == 0 ? 0 : trie[fail[u]][i]);	
					q.push(to);
				} else to = trie[fail[u]][i];
			}
		}
	}
	
	inline void DP() {
		for (int i = tp - 1; i >= 0; i--) {
			int u = topo[i];
            dp[fail[u]] += dp[u];
		}
	}
} AC;

inline void solve() {
    int n;
    cin >> n;
    vector<int> end_point(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        end_point[i] = AC.insert(s);
    }
    AC.build();
    AC.DP();
    for (int i : end_point) cout << AC.dp[i] << '\n';
}

signed main() {
	IO;	
	solve();	
}
