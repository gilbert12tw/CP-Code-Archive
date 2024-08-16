N, M = map(int, input().split())
MOD = 998244353

R = map(int, input().split())
B = map(int, input().split())
rs = [0 for _ in range((1<<N))]
bs = [0 for _ in range((1<<N))]

J = [0 for _ in range(M + 1)]
invJ = [0 for _ in range(M + 1)]

for r in R:
    rs[(1<<(r-1))] += 1
for b in B:
    bs[(1<<(b-1))] += 1
 
for i in range(1, (1<<N)):
    lowbit = i&-i
    if lowbit == i:
        continue
    rs[i] += rs[i ^ lowbit] + rs[lowbit]
    bs[i] += bs[i ^ lowbit] + bs[lowbit]

# build
J[1] = J[0] = invJ[0] = invJ[1] = 1
for i in range(2, M+1):
    J[i] = J[i-1] * i % MOD;
invJ[M] = pow(J[M], MOD - 2, MOD)
for i in range(M - 1, 1, -1):
    invJ[i] = invJ[i + 1] * (i + 1) % MOD

def cal_inv(n, m):
    return invJ[m] * J[n] % MOD * J[m - n] % MOD


# O(3^n) DP
dp = [0 for _ in range((1<<N))]

for i in range(1, 1<<N):
    if rs[i] != bs[i]:
        continue
    dp[i] = cal_inv(rs[i], M)
    subset = (i - 1) & i

    odp = cal_inv(rs[i], M)

    while subset > (i >> 1):
        if rs[subset] == bs[subset]:
            dp[i] -= dp[subset] * invJ[M - rs[subset]] % MOD * J[rs[i] - rs[subset]] % MOD * J[M - rs[i]] % MOD
            dp[i] %= MOD
            if dp[i] < 0: 
                dp[i] += MOD
        subset = (subset - 1) & i
    
print(sum(dp) % MOD) 

