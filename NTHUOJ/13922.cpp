#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> kids(N);
    for (int i = 0; i < N; ++i) {
        int sz;
        cin >> sz;
        while (sz--) {
            int candy;
            cin >> candy;
            kids[i].push_back(candy);
        }
    }

    map<int, vector<int>> table;
    vector<int> c(M, 0);
    for (int i = 0; i < M; i++) {
        cin >> c[i];
    }
    for (int i = M - 1; i >= 0; i--) {
        table[c[i]].push_back(i);
    }

    vector<int> result(M, 0);
    for (int i = 0; i < N; i++) {
        int gg = 1;
        vector<int> chose;
        for (int j : kids[i]) {
            if (table[j].empty()) {
                gg = 0;
                break;
            }
            int c = table[j].back(); table[j].pop_back();
            chose.push_back(c);
        }
        if (gg == 0) break;
        for (int c : chose)
            result[c] = i + 1;
    }

    for (int kid : result) {
        cout << kid << endl;
    }

    return 0;
}

