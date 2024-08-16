#include<bits/stdc++.h>
using namespace std;

const int mxN = 100000 + 5;
int n;
int a[mxN], dp[mxN];

#define ls (u<<1)
#define rs (ls|1)

vector<int> pod;
void post_order(int u) {
    if (ls <= n && a[ls] != -1) post_order(ls);
    if (rs <= n && a[rs] != -1) post_order(rs);
    pod.push_back(a[u]);
}

int ans = 0;
void dfs(int u) {
    if (ls <= n && a[ls] != -1) dfs(ls);
    if (rs <= n && a[rs] != -1) dfs(rs);
    ans = max(ans, dp[ls] + dp[rs]);
    dp[u] = max(dp[ls], dp[rs]) + 1;
}

inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    post_order(1);
    dfs(1);
    cout << ans << '\n';
    for (int i = 0; i < pod.size(); i++) {
        if (i) cout << ' ';
        cout << pod[i];
    }
}

signed main() {
	solve();	
}
