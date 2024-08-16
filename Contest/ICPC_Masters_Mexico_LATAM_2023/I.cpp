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
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

template <typename Cap = int64_t>
class Dinic{
private:
	struct E{
		int to, rev;
		Cap cap;
	};
	int n, st, ed;
	vector<vector<E>> G;
	vector<int> lv, idx;
	bool BFS(){
		lv.assign(n, -1);
		queue<int> bfs;
		bfs.push(st); lv[st] = 0;
		while (not bfs.empty()){
			int u = bfs.front(); bfs.pop();
			for (auto e: G[u]) {
				if (e.cap <= 0 or lv[e.to]!=-1) continue;
				bfs.push(e.to); lv[e.to] = lv[u] + 1;
			}
		}
		return lv[ed] != -1;
	}
	Cap DFS(int u, Cap f){
		if (u == ed) return f;
		Cap ret = 0;
		for(int &i = idx[u]; i < int(G[u].size()); ++i) {
			auto &e = G[u][i];
			if (e.cap <= 0 or lv[e.to]!=lv[u]+1) continue;
			Cap nf = DFS(e.to, min(f, e.cap));
			ret += nf; e.cap -= nf; f -= nf;
			G[e.to][e.rev].cap += nf;
			if (f == 0) return ret;
		}
		if (ret == 0) lv[u] = -1;
		return ret;
	}
public:
	void init(int n_) { G.assign(n = n_, vector<E>()); }
	void add_edge(int u, int v, Cap c){
		G[u].push_back({v, int(G[v].size()), c});
		G[v].push_back({u, int(G[u].size())-1, 0});
	}
	Cap max_flow(int st_, int ed_){
		st = st_, ed = ed_; Cap ret = 0;
		while (BFS()) {
			idx.assign(n, 0);
			Cap f = DFS(st, numeric_limits<Cap>::max());
			ret += f;
			if (f == 0) break;
		}
		return ret;
	}
};

const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

inline void solve() {
  int r, c, d;
  cin >> r >> c >> d;

  Dinic<int> flow;
  vector<string> mat(r);
  vector<vector<int>> id(r, vector<int>(c));

  for (int i = 0; i < r; i++) cin >> mat[i];
  
  int id_cnt = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (mat[i][j] == 'P' || mat[i][j] == 'H' || mat[i][j] == 'S') {
        id[i][j] = ++id_cnt;
        if (mat[i][j] == 'H') {
          ++id_cnt;
        }
      }
    }
  }

  int s = id_cnt + 5, t = s + 1;
  flow.init(2 * r * c + 5);

  auto check = [&r, &c](int x, int y) {
    return (x >= 0 && x < r && y >= 0 && y < c);
  };

  auto bfs = [&](int x, int y, int st_id) {
    vector<vector<int>> dis(r, vector<int>(c, inf));
    dis[x][y] = 0;
    queue<pii> q;
    q.push(x, y);

    flow.add_edge(st_id, st_id + 1, 1);
    while (!q.empty()) {
      auto [nowx, nowy] = q.front(); q.pop();

      if (dis[nowx][nowy] > d) return;

      if (mat[nowx][nowy] == 'S') {
        flow.add_edge(id[nowx][nowy], st_id, 1);
        continue;
      }
      if (mat[nowx][nowy] == 'P') {
        flow.add_edge(st_id + 1, id[nowx][nowy], 1);
        continue;
      }

      for (int d = 0; d < 4; d++) {
        int nx = nowx + dx[d], ny = nowy + dy[d];
        if (check(nx, ny) && (mat[nx][ny] == '.' || mat[nx][ny] == 'S' || mat[nx][ny] == 'P') && dis[nx][ny] == inf) {
          dis[nx][ny] = dis[nowx][nowy] + 1;
          q.push(nx, ny); 
        }
      }
    }

  };
  
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (mat[i][j] == 'H') {
        bfs(i, j, id[i][j]);
      } else if (mat[i][j] == 'P') {
        flow.add_edge(id[i][j], t, 1);
      } else if (mat[i][j] == 'S') {
        flow.add_edge(s, id[i][j], 1);
      }
    }
  }

  cout << flow.max_flow(s, t) << '\n';
}

signed main() {
	IO;	
	solve();	
}
