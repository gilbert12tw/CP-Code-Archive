n, m, x = map(int, input().split())

a, b, s, t = zip(*[tuple(map(int,input().split())) for _ in range(m)])

train = sorted([(s[i], 1, i) for i in range(1, m)] + [(t[i], 0, i) for i in range(m)])

ans = [0] * m
ans[0] = x

dp = [0] * (n + 1)
for tm, tpe, i in train:
    if tpe:
        ans[i] = max(0, dp[a[i]] - s[i])
    else:
        dp[b[i]] = max(dp[b[i]], t[i] + ans[i])

print(*ans[1:])
