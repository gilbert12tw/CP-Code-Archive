#define ll loli
#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(all(x), v)
#define ub(x, v) upper_bound(all(x), v)
#define sz(x) (int)(x.size())
#define re(x) reverse(all(x))
#define uni(x) x.resize(unique(all(x)) - x.begin())
#define all(x) x.begin(), x.end()
#define mem(x, v) memset(x, v, sizeof x); 
#define int long long
#define pii pair<int, int>
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define F first
#define S second
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
#define chmax(a, b) (a = (b > a ? b : a))
#define chmin(a, b) (a = (b < a ? b : a))
#define de(x) cout << #x << " = " << x << endl
#define deb(x, y)  cout << "[" << #x << ", " << #y << "] = " << x << ' ' << y << endl
#define debu(x, y, z) cout << "[" << #x << ", " << #y << ", " << #z << "] = " << x << ' ' << y << ' ' << z << ' ' << endl
#define get_bit(x, y) ((x>>y)&1)
using namespace std;

const int mxN = 1e5 + 5;
int n, m, a[mxN];
vector<array<int, 3>> e;

int dsu[mxN], mxin[mxN], sum[mxN];
void init() {
	for(int i = 1; i <= n; i++) {
		dsu[i] = i;
		sum[i] = a[i];
		mxin[i] = INF;
	}		
}

int get(int x) {
	return dsu[x] == x ? x : dsu[x] = get(dsu[x]);
}

inline void solve() {
	cin >> n >> m;
	e.resize(m);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> e[i][0] >> e[i][1] >> e[i][2];	
	init();
	sort(all(e), [](auto a, auto b) {
		return a[2] > b[2];	
	});

	for (auto [x, y, w] : e) {
		int px = get(x), py = get(y);
		if (px == py) continue;
		n--;
		int res = max(min(mxin[py] - sum[px], w - sum[px]), min(mxin[px] - sum[py], w - sum[py]));
		dsu[px] = dsu[py];
		sum[py] += sum[px];
		mxin[py] = res;
	}

	if (n != 1 or mxin[get(1)] <= 0) cout << -1 << '\n';
	else cout << mxin[get(1)] << '\n';
}

signed main() {
	IO;	
	solve();	
    for (int i = 0; i < n; i++) {
        cin >> a;
    }
}

