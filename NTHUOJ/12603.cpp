#include<stdio.h>
#include<stdlib.h>

int x[200001];
char s[200001];
int main() {
    int n; scanf("%d", &n);
    scanf("%s", s);
    for (int i = 0; i < n; i++) {
        scanf("%d", x + i);
    }

    int mn = -1;
    for (int i = 1; i < n; i++) {
        if (s[i] == 'L' && s[i-1] == 'R') {
            int tmp = x[i] - x[i-1];
            if (mn == -1 || mn > tmp) mn = tmp;
        }
    }
    if (mn == -1) printf("%d\n", mn);
    else printf("%d\n", mn / 2);
}
