#include<bits/stdc++.h>
using namespace std;

const int mxN = (1<<16) + 5;
int L, N;
int a[mxN], mx[mxN], mn[mxN];

#define ls (u<<1)
#define rs (ls|1)

int cnt = 0, gg = 0;
void cal_swap(int u, int dep = 0) {
    if (dep == L - 1) { 
        mx[u] = mn[u] = a[u];
        return;
    }
    cal_swap(ls, dep + 1);
    cal_swap(rs, dep + 1);

    if (mn[ls] >= mx[rs]) {
        cnt++;
    } else if (mx[ls] > mn[rs]) {
        gg = 1;
    }

    mx[u] = max(mx[ls], mx[rs]);
    mn[u] = min(mn[ls], mn[rs]);
}

int dp[mxN];
void dfs_mx(int u, int dep = 0) {
    if (dep == L - 1) {
        dp[u] = a[u];
        return;
    }
    dfs_mx(ls, dep + 1); dfs_mx(rs, dep + 1);
    dp[u] = max(dp[ls], dp[rs]) + a[u];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> L;
    N = (1<<(L)) - 1;
    for (int i = 1; i <= N; i++) 
        cin >> a[i];

    cal_swap(1);
    if (gg) cout << -1 << '\n';
    else cout << cnt << '\n';

    dfs_mx(1);
    cout << dp[1];
}
