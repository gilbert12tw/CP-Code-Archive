#include<bits/stdc++.h>
//#define loli
using namespace std;
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
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 2e5 + 5;
int n, m;
vector<int> tree[mxN];

int pa[mxN];
int dl[mxN], dr[mxN];

int dep[mxN];
int jump[20][mxN];

int tot = 0;
void dfs(int u, int p) {
  pa[u] = p;
  dl[u] = ++tot;

  jump[0][u] = p;
  for (int i = 1; i < 18; i++) {
    jump[i][u] = jump[i-1][jump[i-1][u]];
  }

  for (int v : tree[u]) {
    if (v == p) continue
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
  dr[u] = tot;
}

inline int is_ancestor(int u, int v) {
  return dl[u] <= dl[v] && dr[v] <= dr[u];
}

inline int jump_k(int x, int k) {
  for (int i = 0; i < 18; i++) {
    if (get_bit(k, i))
      x = jump[i][x];
  }
  return x;
}

int lca(int a, int b) {
  if (dep[a] < dep[b]) swap(a, b);
  a = jump_k(a, dep[a] - dep[b]);
  if (a == b) return a;
  for (int i = 17; i >= 0; i--) {
    int ja = jump[i][a];
    int jb = jump[i][b];
    if (ja && jb && ja != jb) {
      a = ja, b = jb;
    }
  }
  return pa[a];
}

inline void solve() {
  cin >> n >> m;
  vector<int> degree(n + 1);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    tree[u].eb(v); tree[v].eb(u);
    degree[u]++; degree[v]++;
  }

  set<int> leaves;
  int root = 0;
  for (int i = 1; i <= n; i++) {
    if (degree[i] > 1)
      root = i;
    else 
      leaves.insert(i);
  }

  root = 1;
  dfs(root, 0);

  int ans = n;
  for (int i = 0; i < m; i++) {
    int a; cin >> a;
    if (SZ(leaves) == 1) {
      cout << 1 << '\n';
      continue;
    }

    int same = 0;
    int vir_root = -1;
    int closest_vertex = -1;
    int above_leaves = 0;
    for (int l : leaves) {
      if (is_ancestor(a, l)) above_leaves = 1;
      if (vir_root == -1) vir_root = l;
      else vir_root = lca(vir_root, l);
      if (a == l) {
        same = 1;
        break;
      }
    }

    // degree = 0 -> deleted
    auto add = [&](int x, int val) {
      degree[x] += val;
      for (int v : tree[x]) {
        if (degree[v] > 0) degree[v] += val;
      }
    };

    set<int> tmp;
    if (same) { // case 1. a is one of the leaves
      ans -= (SZ(leaves) - 1);
    } else if (above_leaves && is_ancestor(vir_root, a)) {  // case 2. a is in the virtual tree
      ans -= SZ(leaves);
    } else { // case 3. a is outside 
      // find closest_vertex
      if (!is_ancestor(vir_root, a)) 
        closest_vertex = vir_root;
      else {
        for (int l : leaves) {
          int lc = lca(a, l);
          if (is_ancestor(vir_root, lc) && (closest_vertex == -1 || dep[lc] > dep[closest_vertex]))
            closest_vertex = lc;
        }
      }

      test(closest_vertex);
      if (leaves.find(closest_vertex) != leaves.end()) {
        ans -= (SZ(leaves) - 1);
        ans++;
      } else {
        ans -= SZ(leaves);
        ans++;
      }
      // add vertext
      if (is_ancestor(closest_vertex, a)) {
        int ad = jump_k(a, dep[a] - dep[closest_vertex] - 1);
        tmp.insert(ad);
        add(ad, 1);
      } else {
        tmp.insert(pa[closest_vertex]);
        add(pa[closest_vertex], 1);
      }
    }

    // move vertex
    for (int l : leaves) {
      if (l == closest_vertex) continue;
      if (l == a) {
        tmp.insert(l);
      } else {
        add(l, -1);
        if (is_ancestor(l, a)) {
          int ad = jump_k(a, dep[a] - dep[l] - 1);
          if (degree[ad] == 1) tmp.insert(ad);
        } else {
          if (degree[pa[l]] == 1) tmp.insert(pa[l]);
        }
      }
    }

    swap(tmp, leaves);

    /*
    cout << "leaves = ";
    for (int l : leaves) cout << l << ' ';
    cout << '\n';
    */

    cout << ans << '\n';
  }
}

signed main() {
	IO;	
	solve();	
}
