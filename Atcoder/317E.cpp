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

int n, m;
string mat[2001];
int blk[2001][2001];
int dis[2001][2001];
pii st, ed;

bool isobc(char c) {
  return (c == '<' || c == '>' || c == 'v' || c == '^' || c == '#');
}

const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int bfs(pii st, pii ed) {
  queue<pii> q;
  memset(dis, -1, sizeof dis);
  dis[st.X][st.Y] = 0;
  q.push(st);
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    for (int d = 0; d < 4; d++) {
      int nx = dx[d] + x, ny = dy[d] + y;
      if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !blk[nx][ny]) {
        if (dis[nx][ny] == -1) {
          dis[nx][ny] = dis[x][y] + 1;
          q.push(nx, ny);
        }
      }
    }
  }
  return dis[ed.X][ed.Y];
}

inline void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> mat[i];
    mat[i] = "#" + mat[i];
  }
  
  for (int i = 1; i <= n; i++) {
    int p = 0;
    for (int j = 1; j <= m; j++) {
      if (mat[i][j] == 'S') {
        st = mkp(i, j);
        continue;
      }
      if (mat[i][j] == 'G') {
        ed = mkp(i, j);
        continue;
      }

      if (isobc(mat[i][j]))
        blk[i][j] = 1;

      // >
      if (p && isobc(mat[i][j])) 
        p = 0;
      if (mat[i][j] == '>') 
        p = 1;
      if (p)
        blk[i][j] = 1;
    }
  }


  // <
  for (int i = 1; i <= n; i++) {
    int p = 0;
    for (int j = m; j >= 1; j--) {
      if (p && isobc(mat[i][j])) 
        p = 0;
      if (mat[i][j] == '<') 
        p = 1;
      if (p)
        blk[i][j] = 1;
    }
  }

  // v
  for (int j = 1; j <= m; j++) {
    int p = 0;
    for (int i = 1; i <= n; i++) {
      if (p && isobc(mat[i][j])) 
        p = 0;
      if (mat[i][j] == 'v') 
        p = 1;
      if (p)
        blk[i][j] = 1;
    }
  }

  // ^
  for (int j = 1; j <= m; j++) {
    int p = 0;
    for (int i = n; i >= 1; i--) {
      if (p && isobc(mat[i][j])) 
        p = 0;
      if (mat[i][j] == '^') 
        p = 1;
      if (p)
        blk[i][j] = 1;
    }
  }

  cout << bfs(st, ed);
}

signed main() {
	IO;	
	solve();	
}
