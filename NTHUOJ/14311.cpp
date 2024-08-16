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
#define mkp make_pair
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

struct Dijkstra {
    int n;
    vector<vector<pii>> mat;
    vector<int> ymai, dis, from;

    Dijkstra(int _n) : n(_n), mat(n, vector<pii>(n, mkp(-1, -1))), ymai(n), dis(n), from(n) {}

    void add_edge(int u, int v, int w, int c) {
        mat[u][v] = mat[v][u] = mkp(w, c); // weight cap
    }

    void add_person(int u, int p) {
        ymai[u] += p;
    }

    void add_path(vector<int> &path, int val) {
        for (int i = 1; i < SZ(path); i++) {
            mat[path[i-1]][path[i]].second += val;
            mat[path[i]][path[i-1]].second += val; 
        }
    }

    vector<int> find_ymai(int st, int lim) { // return path
        int ysy = dijkstra(st, lim);
        // get path
        vector<int> path;
        if (ysy == -1) return path; // not found (empty)
        add_person(ysy, -1);
        int u = ysy;
        path.eb(u);
        while (from[u] != -1) {
            path.eb(from[u]);
            u = from[u];
        }
        reverse(ALL(path));
        return path;
    }

    pair<int, vector<int>> deliver(int st, int dst, int lim) {
        dijkstra(st, lim);
        test(dst, dis[dst]);
        vector<int> path;
        if (dis[dst] == -1) return mkp(-1, path); // not found (empty)
        int u = dst;
        path.eb(u);
        while (from[u] != -1) {
            path.eb(from[u]);
            u = from[u];
        }
        reverse(ALL(path));
        return mkp(dis[dst], path);
    }

    int dijkstra(int s, int lim) {
        for (int i = 1; i < n; i++) dis[i] = from[i] = -1;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push(0, s);
        dis[s] = 0;
        int ysy = -1;
        if (ymai[s] > 0) ysy = s;
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (dis[u] > d) continue;
            for (int v = 1; v < n; v++) {
                int w = mat[u][v].first;
                int cap = mat[u][v].second;
                if (cap < lim || w == -1) continue;
                if (dis[v] == -1 || dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    from[v] = u;
                    pq.push(dis[v] ,v);
                }
                //test(ysy, v, ymai[v], dis[v]);
                if (ymai[v] > 0 && (ysy == -1 || dis[ysy] > dis[v])) {
                    ysy = v;
                }
            }
        }
        return ysy;
    }
};

inline void solve() {
    int n, m, d;
    cin >> n >> m >> d;
    Dijkstra dij(n + 1);
    for (int i = 0; i < d; i++) {
        string s; cin >> s;
        int u, p; cin >> u >> p;
        dij.add_person(u, p);
    }
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        dij.add_edge(u, v, w, c);
    }

    int q; cin >> q;
    map<int, vector<int>> mp;
    map<int, int> ocu, dst, len;
    vector<int> waiting(205, 0);

    auto drop = [&](int id, int no_no = 0) {
        // return path
        if (no_no == 0) dij.add_path(mp[id], ocu[id]);
        int st = mp[id][0];
        auto [dis, path] = dij.deliver(st, dst[id], ocu[id]);
        if (dis == -1) {
            if (no_no) return false;
            cout << "No Way Home\n";
            waiting[id] = 1;
            return false;
        } 
        dis += len[id];
        cout << "Order " << id << " distance: " << dis << '\n';
        mp[id] = path;
        dij.add_path(mp[id], -ocu[id]);
        return true;
    };

    while (q--) {
        string op; cin >> op;
        int id, s, cap;
        if (op == "Order") {
            cin >> id >> s >> cap;
            auto path = dij.find_ymai(s, cap);
            if (path.empty()) cout << "Just walk. T-T\n";
            else {
                cout << "Order " << id << " from: " << path.back() << '\n';
                len[id] = dij.dis[path.back()];
                ocu[id] = cap;
                mp[id] = path;
                dij.add_path(path, -ocu[id]);
            }
        } else if (op == "Drop") {
            cin >> id >> dst[id];
            drop(id);
        } else if (op == "Complete") { 
            cin >> id;
            dij.add_path(mp[id], ocu[id]);
            dij.add_person(dst[id], 1);
            mp[id].clear();
            for (int i = 1; i <= 100; i++) {
                if (waiting[i] == 0) continue;
                if (drop(i, 1)) waiting[i] = 0;
            }
        }
    }
}

signed main() {
	IO;	
	solve();	
}
