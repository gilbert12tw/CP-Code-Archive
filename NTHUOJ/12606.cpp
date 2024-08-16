#include<stdio.h>
#include<stdlib.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

int main() {
    int n, mx = 0, x0, mn = 1000000000;
    scanf("%d", &n);
    scanf("%d", &x0);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        mx = max(mx, x);
        mn = min(mn, x);
    }
    int ans = 0;
    if (mn < x0) ans += (x0 - mn) * 2;
    if (mx > x0) ans += (mx - x0) * 2;
    printf("%d\n", ans);

}
