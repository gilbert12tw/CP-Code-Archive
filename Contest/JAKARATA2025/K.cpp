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
    int n, m, k, q;
    cin >> n >> m >> k >> q;

    int cnt = 0;
    vector<int> vis(n + 1);
    vis[1] = 1;
    cnt = 1;

    map<int, set<pii>> cango; // key -> company, pair -> (u, v)
    vector<set<pii>> edges(n + 1); // pair -> (company, v)

    auto add_edge = [&](int u, int v, int k) -> void {
        if (vis[v]) return;
        if (vis[u]) {
            cango[k].emplace(u, v);
        } else {
            edges[u].emplace(k, v);
        }
    };

    auto del_edge = [&](int u, int v, int k) -> void {
        auto it = edges[u].find(make_pair(k, v));
        if (it != edges[u].end()) edges[u].erase(it);
        it = cango[k].find(make_pair(u, v));
        if (it != cango[k].end()) cango[k].erase(it);
    };

    auto go_by = [&](int k) -> void {
        vector<int> tmp;
        for (auto [u, v] : cango[k]) {
            if (vis[v]) continue;
            vis[v] = 1;
            cnt++;
            tmp.eb(v);
        }
        cango[k].clear();

        for (int u : tmp) {
            for (auto [k, v] : edges[u]) {
                if (vis[v]) continue;
                cango[k].emplace(u, v);
            }
        }
    };

    for (int i = 0; i < m; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        add_edge(u, v, k);
    }

    for (int i = 0; i < q; i++) {
        int o, u, v, k;
        cin >> o;
        if (o == 3) {
            cin >> k;
            go_by(k);
            cout << cnt << '\n';
        } else if (o == 2) {
            cin >> u >> v >> k;
            del_edge(u, v, k);
        } else if (o == 1) {
            cin >> u >> v >> k;
            add_edge(u, v, k);
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
}
