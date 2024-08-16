#include<bits/stdc++.h>
#include<bits/extc++.h>
 
#define F first
#define S second
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
#define mp make_pair
#define mt make_tuple
#define pii pair<int, int>
#define all(x) (x).begin(),(x).end()
 
using namespace std;

namespace DEBUG{ 
	template <typename T, typename T2>
	ostream& operator<<(ostream& os, const pair<T, T2>& pr) {
		os << "( " << pr.first << ", " << pr.second << ")";
		return os;
	}

	template <typename T>
	inline void printv(T l, T r){
		cerr << "DEBUG: [ ";
		for(; l != r; l++)
			cerr << *l << ", ";
		cerr << "]" << endl;
	}
	
	template <typename T>
	inline void _debug(const char* format, T t) {
		cerr << format << '=' << t << endl;
	}
	
	template <class First, class... Rest>
	inline void _debug(const char* format, First first, Rest... rest) {
		while (*format != ',')
			cerr << *format++;
		cerr << '=' << first << ",";
		_debug(format + 1, rest...);
	}

	#define TEST
	#ifdef TEST
	#define debug(...) cerr << "DEBUG: ",_debug(#__VA_ARGS__, __VA_ARGS__)
	#else
	#define debug(...) void(0)
	#define printv(...) void(0)
	#endif
}  // namespace DEBUG

using namespace DEBUG;

/* ----------------------------------------  */
const int N = 1010;
 
struct DSU{
	int p[N], sz[N];

	DSU(){
		for(int i = 0; i < N; i++)
			p[i] = -1, sz[i] = 1;	
	}

	int fp(int x){
		if(p[x] == -1)
			return x;
		p[x] = fp(p[x]);
		return p[x];
	}

	bool U(int x, int y){
		x = fp(x);
		y = fp(y);
		if(x == y)
			return false;
		if(sz[x] > sz[y])
			swap(x, y);
		p[x] = y;
		sz[y] += sz[x];
		return true;
	}

	bool same(int x, int y){
		return fp(x) == fp(y);
	}
}D1, D2, D3;

int n, m;
int forbid[N];
bool adj[N][N];

int dep[N], low[N];
vector<int>G[N];
vector<pair<int, int>>bridge;

void init(){
	for(int i = 1; i <= n; i++)
		dep[i] = low[i] = -1;
}

void tarjan(int x, int px){
	for(auto i : G[x]){
		if(forbid[x] == i)
			continue;
		if(dep[i] == -1){
			dep[i] = low[i] = dep[x] + 1;
			tarjan(i, x);
			low[x] = min(low[x], low[i]);
			if(low[i] > dep[x])
				bridge.push_back(make_pair(i, x));
		}
		else if(i != px)
			low[x] = min(low[x], dep[i]);
	}
}

bool check(int u, int v, int &u1, int &v1){
	if(u1 != u && v1 != u)
		return false;
	if(u1 != u)
		swap(u1, v1);
	return adj[v1][v];
}

void solve(){
	cin >> n >> m;
	vector<pii>chosen;
	for(int i = 0, u, v; i < m; i++){
		cin >> u >> v;
		assert(1 <= u && u <= n && 1 <= v && v <= n);
		adj[u][v] = adj[v][u] = 1;
		if(D1.U(u, v));
		else if(D2.U(u, v));
		else if(D3.U(u, v));
		else
			continue;
		G[u].pb(v);
		G[v].pb(u);
		chosen.pb(mp(u, v));
	}
	set<array<int, 3>>tris;
	for(auto [u, v] : chosen){
		forbid[u] = v;
		forbid[v] = u;
		init();
		for(int i = 1; i <= n; i++)
			if(dep[i] == -1)
				dep[i] = low[i] = 0, tarjan(i, 0);
		forbid[u] = forbid[v] = 0;
        cout << "u, v = " << u << ", " << v << '\n';
        cout << "bridge\n";
		for(auto [u1, v1] : bridge){
            cout << u1 << ' ' << v1 << '\n';
			if(check(u, v, u1, v1) || check(v, u, u1, v1)){
				array<int, 3>ar = {u, v1, v};
				sort(all(ar));
				tris.insert(ar);
			}
		}
		bridge.clear();
	}
	cout << tris.size() << '\n';
    for (auto v : tris) {
        cout << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
    }
    cout << chosen.size() << '\n';
}
 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 1; 
	// cin >> t;
	while(t--)
		solve();
}
