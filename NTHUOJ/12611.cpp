#include<stdio.h>
#include<stdlib.h>

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int x; scanf("%d", &x);
        int sum = 0, is_leap = 0;
        if (x % 400 == 0 || (x % 4 == 0 && x % 100 != 0)) is_leap = 1;
        for (int i = x + 1; ;i++) {
            int leap = 0;
            if (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0)) leap = 1;
            sum = (sum + 365 + leap) % 7;
            if (sum == 0 && is_leap == leap) {
                printf("%d\n", i);
                break;
            }
        }
    }
}
