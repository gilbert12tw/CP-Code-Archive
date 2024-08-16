#include<stdlib.h>
#include<stdio.h>


long long len[55];

char find(int k, long long x) {
    if (x == 1) return 'O';
    if (x == 2 + len[k-1]) return 'u';
    if (x == len[k]) return 'Q';
    if (x < 2 + len[k-1]) return find(k-1, x - 1);
    return find(k-1, x - 2 - len[k-1]);
}

int main() {
    len[1] = 3; 
    for (int i = 2; i <= 50; i++) len[i] = 3 + 2 * len[i-1];

    int k;
    long long l, r;
    while (scanf("%d %lld %lld", &k, &l, &r) != EOF) {
        for (long long i = l; i <= r; i++) printf("%c", find(k ,i+1)); 
        printf("\n");
    }
}
