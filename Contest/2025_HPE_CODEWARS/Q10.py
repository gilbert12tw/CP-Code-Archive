a = int(input())
temp = list(eval(input()))
m = []
for t in temp:
    m.append(tuple(map(int, t)))

mp = {}

for l, r, v in m:
    if l not in mp:
        mp[l] = 0
    if r + 1 not in mp:
        mp[r + 1] = 0
    mp[l] += v;
    mp[r + 1] -= v;

su = 0
ans = 0
for k, v in sorted(mp.items()):
    su += v
    ans = max(ans, su)
print(ans)