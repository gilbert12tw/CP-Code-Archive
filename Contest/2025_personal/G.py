import sys
input = sys.stdin.readline
MOD = 998244353

def main():
    n = int(input())
    a = [0] + list(map(int, input().split()))
    med = [[0]* (n+1) for _ in range(n+1)]
    for l in range(1, n+1):
        tmp = []
        for r in range(l, n+1):
            tmp.append(a[r])
            b = sorted(tmp)
            med[l][r] = b[(r-l)//2]
    dpBig = [[0]*(n+1) for _ in range(n+1)]
    dpMod = [[0]*(n+1) for _ in range(n+1)]
    dpBig[0][0] = 1
    dpMod[0][0] = 1

    for k in range(1, n+1):
        for i in range(k, n+1):
            best_big = 0
            best_mod = 0
            for t in range(k-1, i):
                if dpBig[t][k-1] == 0:
                    continue
                m = med[t+1][i]
                cand_big = dpBig[t][k-1] * m
                if cand_big > best_big:
                    best_big = cand_big
                    best_mod = (dpMod[t][k-1] * m) % MOD
            dpBig[i][k] = best_big
            dpMod[i][k] = best_mod

    out = []
    for k in range(1, n+1):
        out.append(str(dpMod[n][k]))
    sys.stdout.write("\n".join(out))

main()
