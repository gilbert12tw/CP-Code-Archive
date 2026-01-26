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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].eb(v);
        g[v].eb(u);
    }
   
    vector<vector<int>> dep(n);
    vector<int> pa(n);
    auto dfs = [&](int u, int p, int d, auto&& self) -> void {
        dep[d].eb(u);
        pa[u] = p;
        for (int v : g[u]) {
            if (v == p) continue;
            self(v, u, d + 1, self);
        }
    };
    dfs(0, -1, 0, dfs);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (dep[i].empty()) continue;
        int res = SZ(dep[i]);

        int p0 = pa[dep[i][0]];
        bool same = true;
        for (int v : dep[i]) {
            if (p0 != pa[v]) {
                same = false;
                break;
            }
        }
        if (same) res++;
        ans = max(ans, res);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
