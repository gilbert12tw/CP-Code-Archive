import sys
from collections import Counter, defaultdict, deque
from itertools import accumulate, combinations, permutations
from heapq import heappop, heappush
from math import inf

n = int(input())
h = list(map(int, input().split()))
h = [10 ** 18] + h

stk = [0]
ans = [0]

for i in range(1, n + 1, 1):
    while h[stk[-1]] < h[i]:
        stk.pop()

    lst_hi = stk[-1]
    ans.append(ans[lst_hi] + (i-lst_hi) * h[i])
    stk.append(i)

print(*[i + 1 for i in ans[1:]])
