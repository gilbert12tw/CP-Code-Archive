import sys
from collections import Counter, defaultdict, deque
from itertools import accumulate, combinations, permutations
from heapq import heappop, heappush
from math import inf

n, m = map(int, input().split())
a = list(map(int, input().split()))

a = a + a

a[0] %= m
for i in range(1, 2 * n):
    a[i] = (a[i] + a[i-1]) % m

mp = defaultdict(int)
mp[0] = 1
ans = 0

for i, val in enumerate(a):
    if i - n + 1 >= 0:
        mp[a[i-n+1]] -= 1

    ans += mp[val]

    if i < n:
        mp[val] += 1

print(ans)
