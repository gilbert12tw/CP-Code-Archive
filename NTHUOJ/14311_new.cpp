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
#define get_bit(x, y) ((x>>y)&1)
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cerr << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

template<class T> bool ckmin(T& a, const T& b) { return b<a ? a=b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a<b ? a=b, 1 : 0; }

const int mxN = 105;
int n, m, d;
int mat[mxN][mxN], cap[mxN][mxN];
int people[mxN];

int dis[mxN], from[mxN], vis[mxN];

int find_nxt() {
    int id = 0;
    for (int i = 1; i <= n; i++) {
        //test(i, dis[i]);
        if (vis[i] || dis[i] == -1) continue;
        if (!id || dis[id] > dis[i])
            id = i;
    }
    return id;
}

int sp(int st, int lim) {
    for (int i = 1; i <= n; i++) dis[i] = from[i] = -1, vis[i] = 0;
    dis[st] = 0;
    int res = 0; // deliver man
    for (int i = 0; i < n; i++) {
        int u = find_nxt();
        //test(u);
        vis[u] = 1;
        if (!u) break;
        if (people[u] > 0 && (!res || dis[res] > dis[u])) {
            res = u;
        }
        for (int v = 1; v <= n; v++) {
            if (mat[u][v] == 0 || cap[u][v] < lim) continue;
            if (dis[v] == -1 || dis[v] > dis[u] + mat[u][v]) {
                dis[v] = dis[u] + mat[u][v];
                from[v] = u;
            }
            if (people[v] == 0) continue;
            if (!res || dis[res] > dis[v]) {
                res = v;
            }
        }
    }
    return res;
}

vi get_path(int u) {
    vi path;
    do {
        path.eb(u);
        u = from[u];
    } while (u != -1);
    return path;
}

void add_path(vi &path, int val) {
    for (int i = 1; i < SZ(path); i++) {
        cap[path[i-1]][path[i]] += val;
        cap[path[i]][path[i-1]] += val;
    }
}

inline void solve() {
    cin >> n >> m >> d;
    for (int i = 0; i < m + d; i++) {
        string s; cin >> s;
        if (s == "PLACE") {
            int v, c; 
            cin >> v >> c;
            people[v] = c;
        } else {
            int u, v, w, c;
            cin >> u >> v >> w >> c;
            mat[u][v] = mat[v][u] = w;
            cap[u][v] = cap[v][u] = c;
        }
    }

    vector<int> dest(105), cp(105), len(105);
    vector<vector<int>> path_of_order(105);
    int q; cin >> q;
    set<int> queue;
    while (q--) {
        string op; cin >> op;
        int id, src, dst;
        if (op == "Order") {
            cin >> id >> src >> cp[id];
            int res = sp(src, cp[id]);
            len[id] = dis[res];
            if (res == 0) cout << "Just walk. T-T\n";
            else { 
                cout << "Order " << id << " from: " << res << '\n';
                path_of_order[id] = get_path(res);
                people[res]--;
                add_path(path_of_order, -cp[id]);
            }
        } else if (op == "Drop") {
            cin >> id >> dst;
            src = path_of_order[id].back();
            add_path(path_of_order[id], cp[id]);
            sp(src, cp[id]);
            if (dis[dst] == -1) { 
                cout << "No Way Home\n";
                queue.inset(id);
            } else {
                cout << "Order " << id << " distance: " << dis[dst] + len[id] << '\n';
                path_of_order[id] = get_path(dst);
            }
        } else if (op == "Complete") {
            cin >> id;
            people[path_of_order[id][0]]++;
            add_path(path_of_order[id], cp[id]);
            auto it = queue.begin();
            while (it != queue.end()) {
                int id = *it;
            }
        }
    }
}

signed main() {
	IO;	
	solve();	
}
