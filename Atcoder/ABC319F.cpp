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

const int mxN = 505;
int n;
int t[mxN], s[mxN], g[mxN];

vector<int> tree[mxN];

int medicine[11], medicine_cnt = 0, ismedicine[mxN];
int dp[1025];
bitset<505> vis[1025];

int gg = 0;
void init() {
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  int strength = 1;
  bitset<505> tmp; 
  tmp[1] = 1;
  for (int v : tree[1]) {
    if (ismedicine[v] == -1) {
      pq.push(s[v], v);
    }
  }

  while (!pq.empty()) {
    auto [ts, u] = pq.top(); pq.pop();
    if (ts > strength) break;
    strength += g[u];
    tmp[u] = 1;

    for (int v : tree[u]) {
      if (ismedicine[v] == -1) {
        pq.push(s[v], v);
      }
    }
  }

  if (tmp.count() == n) gg = 1;
  dp[0] = strength;
  vis[0] = tmp;
}

void bfs(int msk, int add) {
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  int strength = dp[msk];
  bitset<505> tmp = vis[msk];

  for (int i = 1; i <= n; i++) if (tmp[i]) {
    for (int v : tree[i]) {
      if (tmp[v]) continue;

      if (ismedicine[v] == -1) {
        pq.push(s[v], v);
      } 

      if (ismedicine[v] == add) {
        if (strength > inf / g[v]) {
          strength = inf;
        } else {
          strength *= g[v];
        }
        tmp[v] = 1;
      }
    }
  }

  while (!pq.empty()) {
    auto [ts, u] = pq.top(); pq.pop();
    if (ts > strength) break;
    strength += g[u];
    if (strength > inf) strength = inf;
    tmp[u] = 1;

    for (int v : tree[u]) {
      if (ismedicine[v] == -1 && tmp[v] == 0) {
        pq.push(s[v], v);
      }
    }
  }

  if (tmp.count() == n) gg = 1;
  if (strength > dp[msk | (1<<add)]) {
    dp[msk | (1<<add)] = strength;
    vis[msk | (1<<add)] = tmp;
  } 
}

inline void solve() {
  cin >> n;
  for (int i = 2; i <= n; i++) {
    int p;
    cin >> p >> t[i] >> s[i] >> g[i];
    tree[p].eb(i);
    ismedicine[i] = -1;
    if (t[i] == 2) {
      ismedicine[i] = medicine_cnt;
      medicine[medicine_cnt++] = i;
    }
  }

  init();

  for (int i = 0; i < (1<<medicine_cnt); i++) {
    for (int j = 0; j < medicine_cnt; j++) {
      if (get_bit(i, j) == 0) {
        bfs(i, j);
      }
    }
  }
  
  if (gg) cout << "Yes\n";
  else cout << "No\n";
}

signed main() {
	IO;	
	solve();	
}
