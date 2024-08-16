#include<stdio.h>
#include<stdlib.h>

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        long long a, b, ans = 0;
        scanf("%lld %lld", &a, &b);
        long long test = 9, cnt = 0;
        while (b > test) {
            cnt++;
            test = test * 10 + 9;
        }
        ans = a * cnt;
        printf("%lld\n", ans);
    }
}
