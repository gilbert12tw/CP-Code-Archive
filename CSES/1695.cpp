#include<bits/stdc++.h>
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
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
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
	Dinic(int n_) { G.assign(n = n_, vector<E>()); }
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
    vector<int> get_set_S() {
		queue<int> bfs;
        vector<int> vis(n + 1);
		bfs.push(st); vis[st] = 1;
		while (not bfs.empty()){
			int u = bfs.front(); bfs.pop();
			for (auto e: G[u]) {
				if (e.cap <= 0 || vis[e.to]) continue;
				bfs.push(e.to); vis[e.to] = 1;
			}
		}
        return vis;
    }
};

inline void solve() {
    int n, m;
    cin >> n >> m;
    Dinic<int> dinic(n + 5);
    vector<pii> origin_edge;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dinic.add_edge(u, v, 1);
        dinic.add_edge(v, u, 1);
        origin_edge.eb(u, v);
    }
    dinic.max_flow(1, n);
    auto S = dinic.get_set_S();
    vector<pii> cut;
    for (auto [u, v]: origin_edge) {
        if (S[u] ^ S[v] == 1) 
            cut.eb(u, v);
    }

    cout << SZ(cut) << '\n';
    for (auto [u, v] : cut) 
        cout << u << ' ' << v << '\n';
}

signed main() {
	IO;	
	solve();	
}
