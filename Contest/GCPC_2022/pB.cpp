#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
#define f first
#define s second
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
template <typename... T> void _print(T... args) {
    ((cerr << args << ' '), ...);
    cerr << '\n';
}
#ifdef debug
#define test(args...) _print("[" + string(#args) + "]:", args)
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


const int mxN = 2e7 + 5;
int np[mxN];
vector<int> prime;

void sieve(int n) {
	for(int i = 2; i <= n; i++) {
		if(np[i] == 0) np[i] = i, prime.eb(i);
		for(int j : prime) {
			if(i * j > n) break;
			np[i * j] = j;
			if(np[i] == j) break;
		}
	}
}

inline void solve() {
    int n; cin >> n;
    vector<int> p;
    sieve(20000000);

    bool has_one = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x == 1) {
            has_one = 1;
            continue;
        }
        p.push_back(x);
    }
    if (has_one) p.push_back(1);
    n = SZ(p);

    Dinic<int> dinic;
    dinic.init(n + 5);
    int s = n + 1, t = s + 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (np[p[i] + p[j]] == p[i] + p[j]) {
                if (p[i] % 2) {
                    dinic.add_edge(i, j, 1);
                } else {
                    dinic.add_edge(j, i, 1);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (p[i] % 2) dinic.add_edge(s, i, 1);
        else dinic.add_edge(i, t, 1);
    }
    cout << n - dinic.max_flow(s, t) << '\n';
}

signed main() {
	IO;	
	solve();	
}
