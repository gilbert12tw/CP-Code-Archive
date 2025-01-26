#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef long long ll;

const int MAXN = 200005;
const int LOGN = 20;

int N;
vector<int> tree[MAXN];
int A[MAXN];
int tin[MAXN], tout[MAXN], timer = 0;
int up[MAXN][LOGN];
int depth[MAXN];

void dfs(int u, int p) {
    tin[u] = ++timer;
    up[u][0] = p;
    for (int i = 1; i < LOGN; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
    }
    for (int v : tree[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    tout[u] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int k = LOGN - 1; k >= 0; k--) {
        if (!is_ancestor(up[u][k], v)) {
            u = up[u][k];
        }
    }
    return up[u][0];
}

vector<pair<int, int>> virtual_tree[MAXN];
bool in_S[MAXN];
ll total_sum = 0;
int s[MAXN];

void dfs_virtual(int u) {
    s[u] = in_S[u] ? 1 : 0;
    for (auto &p : virtual_tree[u]) {
        int v = p.first;
        int len = p.second;
        dfs_virtual(v);
        s[u] += s[v];
        total_sum += (ll)s[v] * (ll)(s[0] - s[v]) * len;
    }
    virtual_tree[u].clear(); // Clear for next color
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N-1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    depth[1] = 0;
    dfs(1, 1);

    map<int, vector<int>> color_nodes;
    for (int i = 1; i <= N; i++) {
        color_nodes[A[i]].push_back(i);
    }

    for (auto &entry : color_nodes) {
        vector<int> S = entry.second;
        int total_s = S.size();
        s[0] = total_s; // Use s[0] to store total_s

        // Build virtual tree
        vector<int> nodes = S;
        sort(nodes.begin(), nodes.end(), [&](int u, int v) {
            return tin[u] < tin[v];
        });
        for (int i = 0; i < (int)nodes.size() - 1; i++) {
            int w = lca(nodes[i], nodes[i+1]);
            nodes.push_back(w);
        }
        sort(nodes.begin(), nodes.end(), [&](int u, int v) {
            return tin[u] < tin[v];
        });
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        // Build virtual tree with edge lengths
        sort(nodes.begin(), nodes.end(), [&](int u, int v) {
            return tin[u] < tin[v];
        });
        for (int u : nodes) {
            in_S[u] = false; // Reset in_S
        }
        for (int u : S) {
            in_S[u] = true;
        }
        vector<int> stk;
        for (int u : nodes) {
            while (!stk.empty() && !is_ancestor(stk.back(), u)) {
                stk.pop_back();
            }
            if (!stk.empty()) {
                int len = depth[u] - depth[stk.back()];
                virtual_tree[stk.back()].emplace_back(u, len);
            }
            stk.push_back(u);
        }
        dfs_virtual(nodes[0]);
        // Reset in_S and s
        for (int u : nodes) {
            in_S[u] = false;
            s[u] = 0;
        }
    }

    cout << total_sum << endl;

    return 0;
}
