#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define eb emplace_back
#define ALL(a) a.begin(), a.end()
#define SZ(a) ((int)a.size())

#ifdef debug
template <typename T>
ostream& operator << (ostream &o, vector<T> vec) {
    o << "{"; int f = 0; for (T i : vec) o << (f++ ? " " : "") << i; return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m"; (..., (cerr << a << " ")); cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#endif

inline void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    //freopen((name+".out").c_str(),"w",stdout);
}

struct BIT {
    vector<int> b;
    int n;
    BIT(int _n): b(_n + 1), n(_n) {}
	int qry(int i) {
		int res = 0;
		for (; i > 0; i -= (i&-i)) res += b[i];
		return res;
	}
	void upd(int i, int v) {
		for (; i <= n; i += (i&-i)) b[i] += v; 
	}
};

void solve() {
    int n;
    cin >> n;
    vector<ll> x(n);
    for (ll &i : x) cin >> i;

    vector<vector<pii>> tree(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        tree[a].eb(b, c);
        tree[b].eb(a, c);
    }

    int tok = -1;
    vector<int> st(n), ed(n), seq;
    vector<ll> dep(n), disc;

    auto pre_dfs = [&](int u, int p, auto&& pre_dfs) -> void {
        st[u] = ++tok;
        seq.eb(u);
        disc.eb(dep[u]);
        for (auto [v, w] : tree[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + w;
            pre_dfs(v, u, pre_dfs);
        }
        ed[u] = tok;
    };

    pre_dfs(0, 0, pre_dfs);
    
    // discrete
    sort(ALL(disc));
    disc.resize(unique(ALL(disc)) - disc.begin());

    vector<int> ans(n);
    vector<vector<int>> qry(n);
    for (int i = 0; i < n; i++) {
        if (st[i] > 0) qry[st[i]-1].eb(i);
        qry[ed[i]].eb(i);
        bug(i, st[i], ed[i]);
    }

    BIT bit(n + 5);
    for (int i = 0; i < n; i++) {
        int u = seq[i];
        int d = lower_bound(ALL(disc), dep[u]) - disc.begin() + 1;
        bit.upd(d, 1);
        bug(u, dep[u], d);

        for (int v : qry[u]) {
            int l = lower_bound(ALL(disc), dep[v]) - disc.begin();
            int r = upper_bound(ALL(disc), dep[v] + x[v]) - disc.begin();
            int res = bit.qry(r) - bit.qry(l);
            bug(v, dep[v], l, r, res);
            if (i == st[v] - 1) ans[v] -= res;
            else ans[v] += res;
        }
    }

    for (int i : ans) cout << i-1 << ' ';
    cout << '\n';;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    setIO("car");
    int T; cin >> T;
    while (T--) solve();
}
