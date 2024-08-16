#include<stdio.h>
#include<stdlib.h>

int c[1001], a[1001];
int main() {
    int n, m; 
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", c + i);
    for (int i = 0; i < m; i++) scanf("%d", a + i);

    int ptr = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] <= a[ptr]) ptr++;
    }

    printf("%d\n", ptr);
}
