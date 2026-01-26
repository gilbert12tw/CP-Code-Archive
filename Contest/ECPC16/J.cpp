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

    vector<pair<ll, int>> stk;
    vector<int> tag(n);
    auto dfs_pre = [&](int u, int p, ll dep, auto&& dfs_pre) -> void {
        tag[u]++;
        auto it = lower_bound(ALL(stk), make_pair(dep - x[u], 0));
        if (it != stk.begin()) {
            tag[prev(it)->second]--;
        }

        stk.eb(dep, u);
        for (auto [v, w] : tree[u]) {
            if (v == p) continue;
            dfs_pre(v, u, dep + w, dfs_pre);
        }
        stk.pop_back();
    };

    auto dfs_sum = [&](int u, int p, auto&& dfs_sum) -> void {
        for (auto [v, w] : tree[u]) {
            if (v == p) continue;
            dfs_sum(v, u, dfs_sum);
            tag[u] += tag[v];
        }
    };
    dfs_pre(0, 0, 0, dfs_pre);
    dfs_sum(0, 0, dfs_sum);
    for (int i = 0; i < n; i++) 
        cout << tag[i] - 1 << " \n"[i == n - 1];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    //setIO("car");
    int T; cin >> T;
    while (T--) solve();
}
