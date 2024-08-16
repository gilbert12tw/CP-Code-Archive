#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> ans;
void dfs(int n) {
    if (n == 1) {
        return;
    }
    if (n == 2) {
        //cout << "1 1\n";
        ans.emplace_back(2, 2);
        return;
    }
    dfs(n - 1); // make a[n - 1] = n -1
    //cout << "1 " << n << '\n'; // make a[1 ~ n] = n
    ans.emplace_back(1, n);
    //cout << "1 " << n - 1 << '\n'; // clear (1, n)
    ans.emplace_back(1, n - 1);
    dfs(n - 1);
}

int main() {
    int n; cin >> n;
    dfs(n);
    ans.emplace_back(1, n);
    cout << ans.size() << '\n';
    for (auto [l, r] : ans)
        cout << l << ' ' << r << '\n';
}
