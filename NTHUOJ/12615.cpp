#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int n;
char goal[20] = "ICPCASIASG", tmp[20];
char s[20001];

const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

bool ok(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

char get(int x, int y) {
    return s[x * n + y];
}

int dfs(int x, int y, int pos) {
    if (pos == 10) return 1;
    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (ok(nx, ny) && get(nx, ny) == goal[pos] && dfs(nx, ny, pos + 1)) return 1;
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    int GG = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (get(i, j) == 'I' && dfs(i, j, 1)) {
                GG = 1;
                break;
            }
        }
    }
    if (GG) puts("YES");
    else puts("NO");
}
