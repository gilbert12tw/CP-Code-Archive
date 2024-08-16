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

const int mxN = 1e5 + 5;
int eu[mxN], ev[mxN], ew[mxN];
vector<int> g[mxN];
int vis_edge[mxN], dis[mxN];
int vis[mxN];

struct linear_base {
	int bas[65] = {0}, len = 0;	
	const int mxL = 60;
	void insert(int x) {
		for (int i = mxL; i >= 0; i--) {
			if (get_bit(x, i)) {
				if (bas[i]) x ^= bas[i];
				else {
					bas[i] = x;
					len++;
					break;
				}
			}
		}
	}
	void elimination() {
		for (int i = 0; i < mxL; i++) {
			if (!bas[i]) continue;
			for (int j = i + 1; j <= mxL; j++) {
				if (get_bit(bas[j], i)) bas[j] ^= bas[i];
			}
		}
	}
  int get_max(int res) {
    for (int i = mxL; i >= 0; i--) {
      if ((res ^ bas[i]) > res) res ^= bas[i];
    }
    return res;
  }
  int get_min(int res) {
    for (int i = mxL; i >= 0; i--) {
      if ((res ^ bas[i]) < res) res ^= bas[i];
    }
    return res;
  }
} lb;

void dfs(int u) {
  vis[u] = 1;
  for (int i : g[u]) {
    if (vis_edge[i]) continue;
    vis_edge[i] = 1;
    int v = eu[i] ^ ev[i] ^ u;
    if (vis[v]) {
      lb.insert(dis[u] ^ dis[v] ^ ew[i]);
    } else {
      dis[v] = dis[u] ^ ew[i];
      dfs(v);
    }
  }
}

inline void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> eu[i] >> ev[i] >> ew[i];
    g[eu[i]].eb(i); g[ev[i]].eb(i);
  }
  dfs(1);  
  cout << lb.get_min(dis[n]);
}

signed main() {
	IO;	
	solve();	
}
