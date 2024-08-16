#include<stdio.h>
#include<stdlib.h>

char s[10001], tmp[10001];
int main() {
    int  m;
    scanf("%s", s);
    scanf("%d", &m);
    while (m--) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        l--;
        for (int i = l; i < r; i++) {
            tmp[l + (i + k - l) % (r - l)] = s[i];
        }
        for (int i = l; i < r; i++) s[i] = tmp[i];
    }
    printf("%s\n", s);
}
