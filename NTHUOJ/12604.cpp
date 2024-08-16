#include<stdio.h>
#include<stdlib.h>

int dfs(int row, int n, int rk, int qn, int bl, int bm, int br, int rl, int rr) {
    if (row == n && rk == 0 && qn == 0) return 1;
    int res = 0;
    bl <<= 1; rl <<= 1;
    br >>= 1; rr >>= 1;
    int msk_rk = (bl | bm | br), msk_qn = (msk_rk | rl | rr);
    for (int i = 0; i < n; i++) {
        if (((msk_rk>>i)&1) == 0 && rk > 0) 
            res += dfs(row + 1, n, rk - 1, qn, bl, (bm|(1<<i)), br, (rl|(1<<i)), (rr|(1<<i)));
        if (((msk_qn>>i)&1) == 0 && qn > 0) 
            res += dfs(row + 1, n, rk, qn - 1, (bl|(1<<i)), (bm|(1<<i)), (br|(1<<i)), rl, rr);  
    }
    return res;
}

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        printf("%d\n", dfs(0, n + m, m, n, 0, 0, 0, 0, 0));
    }
}
