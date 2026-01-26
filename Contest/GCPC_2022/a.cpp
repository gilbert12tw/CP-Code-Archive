#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 10;

int n, m;
int tbl[N];

int isqrt(int n) {
    int x = sqrt(n);
    while (x * x < n) {
        x++;
    }
    while (x * x > n) {
        x--;
    }
    return x;
}

void build() {
    for (int i = 1; i < n; i++) {
        int k = n * n - i * i;
        int x = isqrt(k);

        if (x * x == k)
            tbl[i] = x;


//        cout << i << ": " << k << ' ' << x << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    n--, m--;

    build();
    int ans = 1;

    for (int i = 1; i < n; i++) {
        if (!tbl[i])
            continue;
        int w = i, h = tbl[i];
        if ((m * w) % n  == 0)
            ans++;
    }

    cout << ans * (1 + (n != m)) << '\n';
}
