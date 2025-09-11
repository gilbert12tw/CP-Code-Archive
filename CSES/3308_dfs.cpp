#include <bits/stdc++.h>

const int N = 32;

int n, m;
uint32_t adj[N];
int order[N];
int final_color[N];

uint32_t color_mask[N];
int ans_k = N + 1;

bool backtrack(int u_idx, int num_colors) {
    if (u_idx == n) {
        if (num_colors < ans_k) {
            ans_k = num_colors;
            for (int c = 0; c < num_colors; ++c) {
                for (int i = 0; i < n; ++i) {
                    if ((color_mask[c] >> i) & 1) {
                        final_color[i] = c + 1;
                    }
                }
            }
            return true; 
        }
        return false;
    }

    if (num_colors >= ans_k) {
        return false;
    }

    int u = order[u_idx];

    for (int c = 0; c < num_colors; ++c) {
        if ((adj[u] & color_mask[c]) == 0) {
            color_mask[c] |= (1u << u);
            backtrack(u_idx + 1, num_colors);
            color_mask[c] &= ~(1u << u);
        }
    }

    color_mask[num_colors] |= (1u << u);
    backtrack(u_idx + 1, num_colors + 1);
    color_mask[num_colors] &= ~(1u << u);
    
    return ans_k <= n;
}

void solve() {
    std::cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        adj[i] = 0;
        order[i] = i;
        color_mask[i] = 0;
    }
    ans_k = n + 1;

    std::vector<std::pair<int, int>> deg(n);
    for(int i = 0; i < n; ++i) deg[i] = {0, i};

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u; --v;
        adj[u] |= (1u << v);
        adj[v] |= (1u << u);
        deg[u].first++;
        deg[v].first++;
    }

    std::sort(deg.rbegin(), deg.rend());
    for (int i = 0; i < n; ++i) {
        order[i] = deg[i].second;
    }

    backtrack(0, 0);

    std::cout << ans_k << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << final_color[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solve();
    return 0;
}
