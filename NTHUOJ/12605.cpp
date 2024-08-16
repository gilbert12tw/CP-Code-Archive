#include<stdio.h>
#include<stdlib.h>

char s[200001];
int main() {
    int n, m; 
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    char mp[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < m; i++) {
        char a, b;
        scanf(" %c %c", &a, &b);
        for (int j = 0; j < 26; j++) {
            if (mp[j] == a) {
                mp[j] = b;
            } else if (mp[j] == b) {
                mp[j] = a;
            }
        }
    }

    for (int i = 0; i < n; i++) printf("%c", mp[s[i]-'a']);
    printf("\n");
}
