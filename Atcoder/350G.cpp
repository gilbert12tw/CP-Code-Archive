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
#define mod 998244353
#define get_bit(x, y) ((x>>y)&1)
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

struct DSU {
	vector<int> dsu, sz;
	DSU(int n) {
		dsu.resize(n + 1);
		sz.resize(n + 1, 1);
		for (int i = 0; i <= n; i++) dsu[i] = i;
	}
	int get(int x) {
		return (dsu[x] == x ? x : dsu[x] = get(dsu[x]));
	}
	void oni(int a, int b) {
		a = get(a), b = get(b);
		if(a == b) return; 
		if(sz[a] > sz[b]) swap(a, b);
		dsu[a] = b;
		sz[b] += sz[a];
	}
};

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

inline void solve() {
    int n, q;
    cin >> n >> q;
    auto mkp = [&n](int u, int v) {
        return u * (n + 1) + v;
    };
    DSU dsu(n);
    int lst_ans = 0;
    unordered_set<int, custom_hash> st;
    st.reserve(1000000);
    vector<vector<int>> g(n + 1);
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        int opt = 1 + ((a * (1 + lst_ans) % mod) % 2);
        int u = 1 + ((b * (1 + lst_ans) % mod) % n);
        int v = 1 + ((c * (1 + lst_ans) % mod) % n);
        test(opt, u, v);
        if (opt == 1) {
            dsu.oni(u, v);
            st.insert(mkp(u, v));
            st.insert(mkp(v, u));
            g[u].eb(v);
            g[v].eb(u);
        } else {
            lst_ans = 0;
            if (dsu.get(u) == dsu.get(v)) {
                if (SZ(g[u]) > SZ(g[v])) swap(u, v);
                for (int x : g[u]) {
                    if (st.find(mkp(x, v)) != st.end()) {
                        lst_ans = x;
                        break;
                    }
                }
            }
            cout << lst_ans << '\n';
        }
    }
}

signed main() {
	IO;	
	solve();	
}
