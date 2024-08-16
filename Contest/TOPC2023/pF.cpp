#include<bits/stdc++.h>
//#define loli
using namespace std;
typedef long long ll;
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

const int mxN = 2e5 + 5;
int pa[mxN], bcnt = 0;
int dep[mxN];
vector<int> tree[mxN];

void dfs(int u, int p = -1, int deep = 0) {
  dep[u] = deep;
  if (p != -1) pa[u] = p;
  else pa[u] = u;
  for (int v : tree[u]) {
    if (v == p) continue;
    dfs(v, u, deep + 1);
  }
}

struct DSU {
	vector<int> dsu;
	void init(int n) {
		dsu.resize(n + 1);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
	int oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return 0; 
		dsu[a] = b;
    return 1;
	}
} dsu;

void add(int u, int v) {
  if (pa[u] == v || pa[v] == u) {
    bcnt++;
    return;
  }
  u = dsu.get(u);
  v = dsu.get(v);
  while (u != v) {
    test(u, v);
    if (dep[u] < dep[v]) swap(u, v);
    dsu.oni(u, pa[u]);  
    bcnt--;
    u = dsu.get(pa[u]);
  }
}

inline void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<pii> tree_edge, del_edge;
  set<pii> st;
  dsu.init(n + 1);
  for (int i = 0; i < m; i++) {
    pii tmp;
    cin >> tmp.F >> tmp.S;
    if (tmp.F > tmp.S) swap(tmp.F, tmp.S);
    tree_edge.eb(tmp);
  }

  for (int i = 0; i < q; i++) {
    pii tmp;
    cin >> tmp.F >> tmp.S;
    if (tmp.F > tmp.S) swap(tmp.F, tmp.S);
    del_edge.eb(tmp);
    st.insert(tmp);
  }

  vector<pii> ttedge;
  for (auto e : tree_edge) {
    if (st.find(e) == st.end()) {
      ttedge.eb(e);
    }
  }

  for (auto tmp : ttedge) {
    if (dsu.oni(tmp.F, tmp.S)) {
      tree[tmp.F].eb(tmp.S);
      tree[tmp.S].eb(tmp.F);
    }
  }

  reverse(ALL(del_edge));
  for (auto tmp : del_edge) {
    if (dsu.oni(tmp.F, tmp.S)) {
      tree[tmp.F].eb(tmp.S);
      tree[tmp.S].eb(tmp.F);
    }
  }
  reverse(ALL(del_edge));

  memset(dep, -1, sizeof dep);
  for (int i = 1; i <= n; i++) {
    if (dep[i] == -1) 
      dfs(i, -1, 0);
  }

  dsu.init(n+1);

  // add edge doesn't del
  for (auto e : ttedge) {
    add(e.F, e.S);
    test(e.F, e.S);
  }
  test(bcnt);

  vector<int> ans(q);
  for (int i = q - 1; i >= 0; i--) {
    auto e = del_edge[i];
    ans[i] = bcnt;
    add(e.F, e.S);
    test(e.F, e.S, bcnt);
  }
  for (int i = 0; i < q; i++)
    cout << ans[i] << '\n';
}

signed main() {
	IO;	
	solve();	
}
/*
5 7 5
1 2
1 3
1 4
1 5
2 3
3 4
4 5
3 4
2 3
1 2
4 5
1 4
*/
