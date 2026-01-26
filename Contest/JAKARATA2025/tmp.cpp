
#include<bits/stdc++.h>

int main() {
    int n = 10;
    std::vector<std::vector<int>> graph(n + 1);

    for (int i = 0; i < n; i++) {
        graph[i].push_back(i + 1);
    }

    std::function<void(int, int)> dfs = [&](int cur, int prev) {
        std::cout << cur << '\n';
        for (int v : graph[cur]) {
            if (v != prev)
                dfs(v, cur);
        }
    };

    dfs(0, 0);
}
