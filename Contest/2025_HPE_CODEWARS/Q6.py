s = input()

lst = list(eval(s))

s, tar = lst[0], lst[1]

ans = int(1e9)
pre = -1
while s.find(tar) != -1:
    idx = s.find(tar)
    # print(idx)
    if pre != -1:
        ans = min(ans, idx)
    pre = idx
    s = s[idx + len(tar):]
    # print(s)

print(ans if ans != int(1e9) else -1)
