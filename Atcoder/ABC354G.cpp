#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int, int>
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
#define inf 10000000000
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

inline void solve() {
    int n; cin >> n;
    vector<string> s(n);
    vector<int> a(n);
    for (auto &i : s) cin >> i;
    for (auto &i : a) cin >> i;
    
    vector<vector<int>> mat(n, vector<int>(n));
    auto is_sub = [](const string &a, const string &b) -> bool {
        int n = SZ(a), m = SZ(b);
        if (n < m) return false;
        for (int i = 0; i + m - 1 < n; i++) {
            if (a.substr(i, m) == b) 
                return true;
        }
        return false;
    };

    vector<int> isValid(n);
    map<string, int> mp;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        mp[s[i]] = max(mp[s[i]], a[i]);
    }
    for (int i = 0; i < n; i++) {
        if (mp[s[i]] == a[i]) {
            sum += a[i];
            isValid[i] = 1;
            mp[s[i]] = -100;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (!isValid[i] || !isValid[j]) continue;
            if (is_sub(s[i], s[j])) {
                mat[i][j] = 1;
            }
        }
    }
    
    // floyd
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] |= (mat[i][k] & mat[k][j]);
            }
        }
    }

    Dinic dinic;
    dinic.init(2 * n + 10);
    int st = 2 * n + 1, ed = st + 1;
    for (int i = 0; i < n; i++) {
        if (!isValid[i]) continue;
        dinic.add_edge(st, i, a[i]);
        dinic.add_edge(i + n, ed, a[i]);
        for (int j = 0; j < n; j++) {
            if (mat[i][j] && isValid[j]) {
                dinic.add_edge(i, j + n, inf);
            }
        }
    }
    cout << sum - dinic.max_flow(st, ed) << '\n';
}

signed main() {
	IO;	
	solve();	
}
